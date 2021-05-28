
def set_ones(num):
    count = 0
    while num > 0:
        count += (1 if num%2 == 1 else 0)
        num /= 2
    return count

def solve(num):
    count = 0

    while num > 1:
        if num%2 == 0:
            num /= 2
        else:
            # 3 is exception OR want to keep minimum number of 1s
            if num == 3 or (set_ones(num-1) < set_ones(num+1)):
                num -= 1
            else:
                num += 1
        count += 1

    return count


def solution(n):
    # Your code here
    num = int(n)
    return solve(num)

print solution('3')
