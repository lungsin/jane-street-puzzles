import numpy as np
from scipy import integrate
import math

def calc_triangle_area(x1, y1, x2, y2, x3, y3):
    # Method 1: Using the shoelace formula (determinant method)
    area = abs((x1*(y2 - y3) + x2*(y3 - y1) + x3*(y1 - y2))/2)
    return area

def calc_pie_area(y, x):
    rad_sqr = (x**2 + y**2)
    rad = np.sqrt(rad_sqr)
    angle = np.asin(y / rad)
    return angle / 2.0 * rad_sqr - calc_triangle_area(0, 0, x, y, rad, 0)

def calc_overlap(y, x):
    left_rad = np.sqrt(x**2 + y**2) 
    right_rad = np.sqrt((1-x)**2 + y**2)
    triangle_area = calc_triangle_area(x, y, 1 - right_rad, 0, left_rad, 0)
    left_pie = calc_pie_area(y, x)
    right_pie = calc_pie_area(y, 1 - x)
    return left_pie + right_pie + triangle_area

def integrand(y, x):
    left_rad_sqr = x**2 + y**2 
    right_rad_sqr = (1-x)**2 + y**2

    outer_circles = np.pi * 0.25 * (left_rad_sqr + right_rad_sqr)
    overlap_circle = calc_overlap(y, x) 
    return (outer_circles - 2 * overlap_circle) * 8

def outer_integral(x):
    # Integrate over y from 0 to x
    result, error = integrate.quad(lambda y: integrand(y, x), 0, x) 
    return result

# Calculate the double integral from 0 to 0.5
result, error = integrate.quad(outer_integral, 0, 0.5)

print(f"Calculated result: {result:.12f}")
print(f"Estimated error: {error:.2e}")
