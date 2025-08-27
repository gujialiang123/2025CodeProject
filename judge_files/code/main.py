def tanyas_subtraction(n, k):
    """
    Simulates Tanya's subtraction algorithm.
    
    Args:
    n (int): The initial number.
    k (int): The number of subtractions.
    
    Returns:
    int: The result after k subtractions.
    """
    for _ in range(k):
        # Check if the last digit of the number is zero
        if n % 10 == 0:
            # Remove the last digit (divide by 10)
            n //= 10
        else:
            # Subtract one from the number
            n -= 1
    
    return n

def main():
    # Read input from user
    n, k = map(int, input().split())
    
    # Simulate Tanya's subtraction algorithm
    result = tanyas_subtraction(n, k)
    
    # Print the result
    print(result)

if __name__ == "__main__":
    main()
