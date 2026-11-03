// . Recursive – Print Fibonacci Series
#include <iostream>
using namespace std;

int fibonacci(int n) {
    if (n <= 1)
        return n;

    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
    int n;
    cout << "Enter number of terms: ";
    cin >> n;

    cout << "Fibonacci Series: ";

    for (int i = 0; i < n; i++) {
        cout << fibonacci(i) << " ";
    }

    return 0;
}

Input: 7
Output: 0 1 1 2 3 5 8

// 2. Recursive – Find a Particular Fibonacci Number
#include <iostream>
using namespace std;

int fibonacci(int n) {
    if (n <= 1)
        return n;

    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
    int n;
    cout << "Enter position: ";
    cin >> n;

    cout << "Fibonacci number: " << fibonacci(n);

    return 0;
}

Input: 6
Output: 8

// 3. Non-Recursive – Print Fibonacci Series
#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter number of terms: ";
    cin >> n;

    int a = 0, b = 1, next;

    cout << "Fibonacci Series: ";

    for (int i = 0; i < n; i++) {
        cout << a << " ";

        next = a + b;
        a = b;
        b = next;
    }

    return 0;
}

Input: 7
Output: 0 1 1 2 3 5 8

// 4. Non-Recursive – Find a Particular Fibonacci Number
#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter position: ";
    cin >> n;

    int a = 0, b = 1, next;

    if (n == 0) {
        cout << "Fibonacci number: " << 0;
    }
    else {
        for (int i = 2; i <= n; i++) {
            next = a + b;
            a = b;
            b = next;
        }

        cout << "Fibonacci number: " << b;
    }

    return 0;
}