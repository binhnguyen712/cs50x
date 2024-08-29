from cs50 import get_int
import re
def main():
    card_number = get_int("Number: ")
    if re.search("^3[47]\d{13}", str(card_number)):
            valid = check_valid(card_number)
            if valid == True:
                print("AMEX")
            else:
                print("INVALID")
    elif re.search("^5[1-5]\d{14}", str(card_number)):
            valid = check_valid(card_number)
            if valid == True:
                print("MASTERCARD")
            else:
                print("INVALID")
    elif re.search("^4\d{12}", str(card_number)) or re.search("^4\d{15}", str(card_number)):
            valid = check_valid(card_number)
            if valid == True:
                print("VISA")
            else:
                print("INVALID")
    else:
         print("INVALID")



def check_valid(card_number):
    def todigits(card_number):
         return [int(d) for d in str(card_number)]
    digits = todigits(card_number)
    odd_digits = digits[-1::-2]
    even_digits = digits[-2::-2]
   # print(odd_digits)
    #print(even_digits)
    sum1 = sum(odd_digits)
   # print(sum1)

    for d in even_digits:
        if d*2 > 9:
            sum1 += d*2 // 10 + d*2 % 10
        else:
            sum1 += d*2
    if sum1 % 10 == 0:
         return True
    else:
         return False

main()
