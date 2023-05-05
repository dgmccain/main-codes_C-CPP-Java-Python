import operator

encryptedMessage = "fzpgtofucfukqmzvftfuktofgzftouqmfmtosopvfupenopajttoptzqjeduqtzqvcgqolvlpvlgqrllggqvvifmtolzlfvdkvprrpvtovlziqjqmmfopdtqdqfttqopyluqlgptmfvgttolulbttzqrlggpklgfmdlsqdldzfeeelpdiqjtqpnvfxlajtqueitolmfvgtnlvgquzoqdqlgftzfeeklttolnvfxlalspjglpgiqjcuqzpgptlpsolvfpruqtgqvfsofmiqjgqeylhjlgtfqutzqmfvgtiqjzfeekltpmvllsqniqmtolsqdlaqqcfmiqjgqeylhjlgtfqutvollmfvgtiqjzfeeklttludqeepvgkqqdejsc"
storedLetters = {}
dictionary = {'e': 12.70, 't': 9.06, 'a': 8.17, 'o': 7.51, 'i': 6.97, 'n': 6.75, 's': 6.33, 'h': 6.09, 'r': 5.99, 'd': 4.25, 'l': 4.03, 'c': 2.78, 'u': 2.76, 'm': 2.41, 'w': 2.36, 'f': 2.23, 'g': 2.02, 'y': 1.97, 'p': 1.93, 'b': 1.29, 'v': 0.98, 'k': 0.77, 'j': 0.15, 'x': 0.15, 'q': 0.10, 'z': 0.07}

#store encrypted letter frequency
for letter in encryptedMessage:
  if letter in storedLetters:
    storedLetters[letter] += 1
  else:
    storedLetters[letter] = 1

#account for letter that was not in encryptedMessage
storedLetters.update({'w': 0})

#encrypted letters frequency in descending order
sortedEncryptedLetters = sorted(storedLetters.items(), key=operator.itemgetter(1), reverse=True)
#dictionary letters frequency in descending order
sortedDictionary = sorted(dictionary.items(), key=operator.itemgetter(1), reverse=True)

#display letter frequency data
print(sortedEncryptedLetters)
print()
print(sortedDictionary)

#2 decryption methods:
#try substitutions based upon most/least frequent letters...
#try bigram and trigram analysis...

#display decrypted message - assuming that ciphertext was
#converted to plaintext using previously mentioned methods...
print()
print(encryptedMessage)