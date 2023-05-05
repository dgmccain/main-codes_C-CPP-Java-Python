#encryption and decryption variables
ciphertext = "qknvbdradnrlbexrbmzilqkzenqkpbgqvnzwbgbnlazkfvnfybblqhybqhenoqnzzspdpnlqkzenlwybkvlwbaimfdkeanliznrlbebmfdlubnlanzhaebkokdblfdsfmrybsvzitzrfrlnihspczpyzmtosnednmlfdmqhsybmrmgnhnzmdglizrttqchqlqgpfqknzmdgmwskeenwtvxpttmnpmdbnptenarqlowqpnffbzkkqbpybbmfdogdmnffkbdsgmqnpbltlqlfdfbzkkqmqtqcyaeznfnbqkqqhlkqhzbbrixlwyzmtmcebiqfdrttqht"
plaintext = "themainr"
ciphertextLen = len(ciphertext)
plaintextLen = len(plaintext)
#known conversion variables - based upon plaintext of 8 letters
knownCipher1 = "qk"
knownCipher2 = "nv"
knownCipher3 = "bd"
knownCipher4 = "ra"
knownPlain1 = "th"
knownPlain2 = "em"
knownPlain3 = "ai"
knownPlain4 = "nr"
#guesses for conversion based on discovered values
  #leave in the 5 highest occurring bigrams
knownCipher5 = "fd"
knownPlain5 = "he" #correct guess based on letter frequency
knownCipher6 = "yb" #after decrypting by pen and paper, yb==ti
knownCipher7 = "en" #after decrypting by pen and paper, en==ve
knownCipher8 = "nz" #after decrypting by pen and paper, nz==re
knownCipher9 = "qh" #after decrypting by pen and paper, qh==ha
  #based on ciphertext bigram letter frequency, nz/pb == at/er/is
  #^^^after decrypting by pen and paper, pb == is and nz == re
#guesses based on first letters likely being "themainreason"
guessCipher1 = "dn"
guessCipher2 = "rl"
guessPlain1 = "ea"
guessPlain2 = "so"
#known soution - after pen and paper method
solution = "THEMAINREASONIWANTEDTOGIVETHISHOMEWORKASQSIGNMENTISTHATIHAVEMOREPRIZESTOGIVEOUTIFYOUARETHEFIRSTPERSONINTHECLASQSREADINGTHISTHENCONTINUEDOINGSOBECAUSEIWILQLREVEALTHELOCATIONOFAFREQECODEBOQOKGOTOHECTHREQEFOURFIVEYOUWILQLSEQEASILVERNOTGOLDENKNIGHTSITINTHEGREQENCHAIRCLOSESTQTOTHEKNIGHTLOQOKUNDERNEATHTHATCHAIRANDYOUWILQLFINDTHEBOQOKQ"


#store ciphertext in file with letters in pairs
f = open("ciphertext.txt", 'w')
for i in range(ciphertextLen):
  f.write(ciphertext[i])
  if((i+1)%2 == 0):
    f.write(" ")
f.close()


#store plaintext with all known values filled in
f = open("plaintext.txt", 'w')
#compare every other letter - will not compare past range
for i in range(0, ciphertextLen, 2):
  tempStr = ciphertext[i]+ciphertext[i+1]
  if(tempStr == knownCipher1):
    f.write(knownPlain1)
    f.write(" ")
    continue
  if(tempStr == knownCipher2):
    f.write(knownPlain2)
    f.write(" ")
    continue
  if(tempStr == knownCipher3):
    f.write(knownPlain3)
    f.write(" ")
    continue
  if(tempStr == knownCipher4):
    f.write(knownPlain4)
    f.write(" ")
    continue
  else:
    f.write('__ ') #unknown values
f.close()


#store plaintext with guesses filled in
f = open("guessing.txt", 'w')
f.write("    plaintext with guesses filled in:\n")
for i in range(0, ciphertextLen, 2):
  tempStr = ciphertext[i]+ciphertext[i+1]
  if(tempStr == knownCipher1):
    f.write(knownPlain1)
    f.write(" ")
    continue
  if(tempStr == knownCipher2):
    f.write(knownPlain2)
    f.write(" ")
    continue
  if(tempStr == knownCipher3):
    f.write(knownPlain3)
    f.write(" ")
    continue
  if(tempStr == knownCipher4):
    f.write(knownPlain4)
    f.write(" ")
    continue
  if(tempStr == knownCipher5):
    f.write(knownPlain5)
    f.write(" ")
    continue
  if(tempStr == guessCipher1):
    f.write(guessPlain1)
    f.write(" ")
    continue
  if(tempStr == guessCipher2):
    f.write(guessPlain2)
    f.write(" ")
    continue
  else:
    f.write('__ ') #unknown values
f.write("\n\n    plaintext with high frequency bigrams:\n")
#display plaintext again with high frequency bigrams
for i in range(0, ciphertextLen, 2):
  tempStr = ciphertext[i]+ciphertext[i+1]
  if(tempStr == knownCipher1):
    f.write(knownPlain1)
    f.write(" ")
    continue
  if(tempStr == knownCipher2):
    f.write(knownPlain2)
    f.write(" ")
    continue
  if(tempStr == knownCipher3):
    f.write(knownPlain3)
    f.write(" ")
    continue
  if(tempStr == knownCipher4):
    f.write(knownPlain4)
    f.write(" ")
    continue
  if(tempStr == knownCipher5):
    f.write(knownPlain5)
    f.write(" ")
    continue
  if(tempStr == knownCipher6):
    f.write(knownCipher6)
    f.write(" ")
    continue
  if(tempStr == knownCipher7):
    f.write(knownCipher7)
    f.write(" ")
    continue
  if(tempStr == knownCipher8):
    f.write(knownCipher8)
    f.write(" ")
    continue
  if(tempStr == knownCipher9):
    f.write(knownCipher9)
    f.write(" ")
    continue
  if(tempStr == guessCipher1):
    f.write(guessPlain1)
    f.write(" ")
    continue
  if(tempStr == guessCipher2):
    f.write(guessPlain2)
    f.write(" ")
    continue
  else:
    f.write('__ ') #unknown values
f.close()


#store solution
f = open("solution.txt", 'w')
for i in range(0, ciphertextLen, 2):
  f.write((solution[i]+solution[i+1]).lower())
  f.write(" ")
f.close()