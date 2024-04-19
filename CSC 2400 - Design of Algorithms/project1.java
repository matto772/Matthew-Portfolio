//Matthew Ogurkis
//CSC 2400
//Fixed: 10/4/2023
import java.util.Scanner;
import java.lang.Math;

class project1 {
    // Creating a method to implement the extended Euclid's algorithm
    public static void euclidsAlgorithm(int m, int n) {
        int temp;
        int x = 0;
        int y = 1;
        int lastX = 1;
        int lastY = 0;

        int originalM = m;
        int originalN = n;

        // Check if both m and n are zero if so, handle it
        if (m == 0 && n == 0) 
        {
            System.out.println("GCD: (0, 0) = undefined.");
            return;
        }

        //handle negative inputs by taking their absolute values
        m = Math.abs(m);
        n = Math.abs(n);

        while (n != 0) {
            int q = m / n;
            int r = m % n;

            m = n;
            n = r;

            temp = x;
            x = lastX - q * x;
            lastX = temp;

            temp = y;
            y = lastY - q * y;
            lastY = temp;
        }

        if (m == 1) {
            System.out.println("GCD: (" + originalM + ", " + originalN + ") = 1, with roots " + x + " and " + y + ".");
        } else {
            System.out.println("GCD: (" + originalM + ", " + originalN + ") = undefined.");
        }
    }

    // Creating a method to implement the constant integer checking algorithm
    public static int constantIntCheck(int m, int n) {
        int t = Math.abs(Math.min(m, n)); //taking the abs to handle negatives

        while (t > 0) 
        {
            if (m % t == 0 && n % t == 0) 
            {
                return t;
            }
            t--;
        }

        // Check if both m and n are zero
        if (m == 0 && n == 0) 
        {
            return 0; // Return 0 for undefined
        }

        return 1; // Return 1 if no gcd found 
    }

    public static void main(String[] args) {
        int m, n, result, choice;
        boolean go = true;
        Scanner superScan = new Scanner(System.in);

        do {
            System.out.println("Please enter your first number: ");
            m = superScan.nextInt();
            System.out.println("Please enter your second number: ");
            n = superScan.nextInt();

            System.out.println("1. Euclid's Extended Algorithm");
            System.out.println("2. Constant Integer Check");
            System.out.println("3. END PROGRAM");
            System.out.println("Which way would you like your GCD calculated?:");
            choice = superScan.nextInt();

            switch (choice) {
                case 1:
                    euclidsAlgorithm(m, n);
                    break;
                case 2:
                    result = constantIntCheck(m, n);
                    if (result == 0) {
                        System.out.println("GCD of " + m + " and " + n + " is: undefined");
                    } 
                    else 
                    {
                        System.out.println("GCD of " + m + " and " + n + " is: " + result);
                    }
                    break;
                case 3:
                    go = false;
                    break;
                default:
                    System.out.println("Invalid option!");
            }

        } while (go);
        superScan.close();
    }
}



































































































