def main():
    text = input("Text: ")

    # count the number of letters, words and sentences
    letters = count_letters(text)
    words = count_words(text)
    sentences = count_sentences(text)

    # Coleman-Liau index
    L = (letters / words) * 100
    S = (sentences / words) * 100
    index = round(0.0588 * L - 0.296 * S - 15.8)

    # print the grade
    if index < 1:
        print("Before Grade 1")

    elif index >= 16:
        print("Grade 16+")

    else:
        print(f"Grade {index}")


def count_letters(text):
    num_letter = 0
    for i in range(len(text)):
        if text[i].isalpha():
            num_letter += 1
    return num_letter


def count_words(text):
    num_words = 1
    for i in range(len(text)):
        if text[i].isspace():
            num_words += 1

    return num_words


def count_sentences(text):
    num_sentence = 0
    for i in range(len(text)):
        if text[i].endswith(".") or text[i].endswith("!") or text[i].endswith("?"):
            num_sentence += 1
    return num_sentence


main()
