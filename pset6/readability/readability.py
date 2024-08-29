from cs50 import get_string
text = get_string("Text: ")

end =["?", "!", "."]
words = len(text.split())
sentences = 0
letters = 0

for i in text:
    if i in end:
        sentences += 1
    if i.isalpha():
        letters += 1

index = round(0.0588 * (letters / words) *100 - 0.296 * (sentences / words) *100 - 15.8)
'''print(words)
print(letters)
print(sentences)
print(index)'''
if index >= 16:
    print("Grade 16+")
elif index < 1:
    print("Before Grade 1")
else:
    print(f"Grade {index}")
