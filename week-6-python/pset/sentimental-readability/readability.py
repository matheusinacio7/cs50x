from cs50 import get_string
import re


text = get_string('Text: ')
word_count = len(text.split())
letter_count = len([char for char in list(text) if char.isalpha()])
sentences = re.split(r'[\.\!\?]+', text)
sentences = list(filter(lambda s: s.strip() and len([char for char in list(s) if char.isalpha()]), sentences))
sentence_count = len(sentences)
L = letter_count / (word_count / 100)
S = sentence_count / (word_count / 100)
index = round(0.0588 * L - 0.296 * S - 15.8)
if (index < 1):
    print("Before Grade 1")
elif (index > 15):
    print("Grade 16+")
else:
    print(f"Grade {index}")
