# Python

def fastmodexp(base,exp,mod):
  # Variables for loop
  numerator = exp
  denominator = 2
  result = 1

  # Update result throughout iterative process
  while(numerator > 0):
    if(numerator%denominator):
      result = (result*base)%mod
    numerator = int(numerator/denominator)
    base = (base*base)%mod

  # Exit loop after checking 1%2 scenario
  return result

def main():
  b = 3
  e = 43
  m = 83

  myAns = fastmodexp(b, e, m)
  print(myAns)
  # Convert bin(exp) to better understand Fastmodexp function

# Run program
main()