import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash
import datetime
from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # portfolio = db.execute("SELECT symbol, shares, price, cash FROM transactions JOIN users ON transactions.account_id = users.id WHERE users.id = ?", session["user_id"])
    portfolio = db.execute("SELECT symbol, SUM(shares) AS shares, price FROM transactions WHERE account_id = ? GROUP BY symbol HAVING SUM(shares) > 0", session["user_id"])
    wallet = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
    total = 0
    for stock in portfolio:
        stock_data = lookup(stock["symbol"])
        total += stock_data["price"] * stock["shares"]
    return render_template("index.html", portfolio=portfolio, wallet=wallet[0]["cash"],total=total)



@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")
    else:
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("Missing symbol")
        stock = lookup(symbol)
        if stock == None:
            return apology("Invalid stock")

        shares = request.form.get("shares")
        try:
            shares = int(shares)
        except ValueError:
            return apology("share must be an integer")
        if shares <= 0:
            return apology("Invalid number of shares.")

        wallet = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        if float(wallet[0]["cash"]) < shares*stock["price"]:
            return apology("You are broke!")

        date = datetime.datetime.now()
        update_wallet = float(wallet[0]["cash"]) - shares*stock["price"]
        db.execute("UPDATE users SET cash = ? WHERE id = ?", update_wallet, session["user_id"])
        db.execute("INSERT INTO transactions (account_id, symbol, shares, price, date) VALUES (?,?,?,?,?)", session["user_id"], stock["symbol"], shares, stock["price"], date)
        flash("Bought!")
        return redirect("/")

@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transactions = db.execute("SELECT * FROM transactions WHERE account_id = ?", session["user_id"])
    return render_template("history.html", transactions=transactions)

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method =="GET":
        return render_template("quote.html")
    else:
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("missing symbol")
        stock = lookup(symbol)
        if stock == None:
            return apology("invalid symbol")
        else:
            return render_template("quoted.html", symbol=stock["symbol"], price=stock["price"])


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "GET":
        return render_template("register.html")
    else:
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        found = False
        if not username or not password or not confirmation:
            return apology("Fill in the missing field")

        rows=db.execute("SELECT username FROM users")
        if password != confirmation:
            return apology("Password and confirmation password not match")
        for row in rows:
            if username == row["username"]:
                found = True
                return apology("Username already exist")
        if found == False and password == confirmation:
            new_user=db.execute("INSERT INTO users (username, hash) VALUES (?,?)", username, generate_password_hash(password, method='pbkdf2', salt_length=16))
            session["user_id"] = new_user
            return redirect('/')


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method =="GET":
        symbols = db.execute("SELECT symbol FROM transactions WHERE account_id = ? GROUP BY symbol HAVING SUM(shares) > 0",session["user_id"])
        return render_template("sell.html", symbols = [row["symbol"] for row in symbols] )
    else:
        shares = int(request.form.get("shares"))
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("Must give symbol")
        stock = lookup(symbol)
        if stock == None:
            return apology("Invalid stock")
        total_shares = db.execute("SELECT SUM(shares) AS shares FROM transactions WHERE account_id = ? AND symbol =? GROUP BY symbol", session["user_id"], symbol)
        if shares < 0 or shares > total_shares[0]["shares"]:
            return apology("Invalid number of shares.")
        wallet = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        update_wallet = shares*stock["price"] + wallet[0]["cash"]
        db.execute("UPDATE users SET cash = ? WHERE id = ?", update_wallet, session["user_id"])
        date=datetime.datetime.now()
        db.execute("INSERT INTO transactions (account_id, symbol, shares, price, date) VALUES (?,?,?,?,?)", session["user_id"], stock["symbol"], (-1)*shares, stock["price"], date)
        flash("Sold!")
        return redirect("/")

