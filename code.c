#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// Fungsi yang akan diintegralkan: f(T) = 0.132 + 1.56e-4*T + 2.64e-7*T^2
double function(double T) {
    return 0.132 + 1.56e-4 * T + 2.64e-7 * T * T;
}

// Metode Trapesium
double trapezoidal_rule(double a, double b, double h) {
    int n = (int)((b - a) / h);
    double sum = 0.0;
    
    // Hitung f(a) + f(b)
    sum = function(a) + function(b);
    
    // Hitung 2 * sum dari f(xi) untuk i = 1 hingga n-1
    for (int i = 1; i < n; i++) {
        double x = a + i * h;
        sum += 2.0 * function(x);
    }
    
    // Kalikan dengan h/2
    return (h / 2.0) * sum;
}

// Hitung nilai eksak menggunakan integral analitik
double exact_value() {
    double a = -100.0, b = 200.0;
    
    // Integral dari 0.132 + 1.56e-4*T + 2.64e-7*T^2
    // = 0.132*T + 1.56e-4*T^2/2 + 2.64e-7*T^3/3
    // = 0.132*T + 0.78e-4*T^2 + 0.88e-7*T^3
    
    double result_b = 0.132 * b + 0.78e-4 * b * b + 0.88e-7 * b * b * b;
    double result_a = 0.132 * a + 0.78e-4 * a * a + 0.88e-7 * a * a * a;
    
    return 1000.0 * (result_b - result_a);
}

int main() {
    double a = -100.0;  // batas bawah
    double b = 200.0;   // batas atas
    
    // Array step sizes
    double step_sizes[] = {300, 150, 100, 75, 50, 25, 10, 5, 1, 0.5};
    int num_steps = sizeof(step_sizes) / sizeof(step_sizes[0]);
    
    // Hitung nilai eksak
    double exact = exact_value();
    
    printf("Perhitungan Integral Kalor Jenis menggunakan Metode Trapesium\n");
    printf("Fungsi: f(T) = 0.132 + 1.56e-4*T + 2.64e-7*T^2\n");
    printf("Batas integral: dari %.1f hingga %.1f\n", a, b);
    printf("Nilai eksak (analitik): %.6f\n\n", exact);
    
    printf("+-----------+------------------+------------------+------------------+\n");
    printf("| Step Size |    Hasil Numerik |      Error Abs   |   Error Relatif  |\n");
    printf("+-----------+------------------+------------------+------------------+\n");
    
    for (int i = 0; i < num_steps; i++) {
        double h = step_sizes[i];
        
        // Pastikan step size tidak lebih besar dari interval
        if (h > (b - a)) {
            printf("| %9.1f | Step size terlalu besar untuk interval |\n", h);
            continue;
        }
        
        // Hitung menggunakan metode trapesium
        double integral_result = trapezoidal_rule(a, b, h);
        double final_result = 1000.0 * integral_result;
        
        // Hitung error
        double error_abs = fabs(final_result - exact);
        double error_rel = (error_abs / fabs(exact)) * 100.0;
        
        printf("| %9.1f | %16.6f | %16.6f | %15.4f%% |\n", h, final_result, error_abs, error_rel);
}
    
    printf("+-----------+------------------+------------------+------------------+\n");
    
    // Analisis konvergensi
    printf("\nAnalisis Konvergensi:\n");
    printf("Semakin kecil step size, semakin akurat hasil perhitungan.\n");
    printf("Error berkurang secara kuadratik dengan pengurangan step size.\n");
    
    // Informasi tambahan tentang jumlah subinterval
    printf("\nInformasi Jumlah Subinterval:\n");
    printf("+-----------+------------------+\n");
    printf("| Step Size | Jumlah Interval  |\n");
    printf("+-----------+------------------+\n");
    
    for (int i = 0; i < num_steps; i++) {
        double h = step_sizes[i];
        if (h <= (b - a)) {
            int n = (int)((b - a) / h);
            printf("| %9.1f | %16d |\n", h, n);
        }
    }
    printf("+-----------+------------------+\n");
    
    return 0;
}