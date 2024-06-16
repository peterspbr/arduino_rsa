void setup() {
    Serial.begin(9600);

    unsigned long m = 4356; // Max of 5140
    Serial.print("Original message: ");
    Serial.println(m);

    unsigned long p = 53;
    unsigned long q = 97;
    unsigned long n = p*q;
    unsigned long phi = (p-1) * (q-1);
    unsigned long e = 17;

    Serial.print("p: ");
    Serial.println(p);

    Serial.print("q: ");
    Serial.println(q);

    Serial.print("n: ");
    Serial.println(n);

    Serial.print("Phi: ");
    Serial.println(phi);

    Serial.print("exponent: ");
    Serial.println(e);

    // Compute
    unsigned long d = modInverse(e, phi); // d = e^-1 mod phi

    Serial.print("Decryption key: ");
    Serial.println(d);

    // Encrypt the message: c = m^e % n
    unsigned long ciphertext;
    ciphertext = powermod(m, e, n);

    Serial.print("Ciphertext: ");
    Serial.println(ciphertext);

    // Decrypt the message: m = c^d % n
    unsigned long decryptedMessage;
    decryptedMessage = powermod(ciphertext, d, n);

    Serial.print("Plaintext: ");
    Serial.println(decryptedMessage);
}

unsigned long powermod(unsigned long base, unsigned long exponent, unsigned long modulus) {
    unsigned long result = 1;
    base = base % modulus; // Ensure base is within modulus range

    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % modulus;
        }
        base = (base * base) % modulus;
        exponent /= 2;
    }

    return result;
}

unsigned long modInverse(unsigned long a, unsigned long m) {
    long long m0 = m;
    long long y = 0, x = 1;

    if (m == 1) return 0;

    while (a > 1) {
        long long q = a / m;
        long long t = m;

        m = a % m;
        a = t;
        t = y;

        y = x - (q * y);
        x = t;
    }

    if (x < 0) x += m0;

    return x;
}

void loop() {
    // Empty loop, since we only want setup to run once
}
