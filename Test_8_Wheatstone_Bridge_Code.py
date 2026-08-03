import machine
import time

adc_A = machine.ADC(26)
adc_B = machine.ADC(27)

VOLTAGE_FACTOR = 3.3 / 65535

print("--- Wheatstone Bridge Live Test (1k / 2k Pairs) ---")
print("Expected Balance Point: ~2.2000 V")
print("Press Ctrl+C to stop.\n")
print(f"{'V_A (V)':<10}{'V_B (V)':10}{'V_out (Diff)':<15}")
 
while True:
    raw_A = sum([adc_A.read_u16() for _ in range(30)]) / 30
    raw_B = sum([adc_B.read_u16() for _ in range(30)]) / 30
    
    v_A = raw_A * VOLTAGE_FACTOR
    v_B = raw_B * VOLTAGE_FACTOR
    
    v_out = v_A - v_B
    
    print(f"{v_A:.4f}	{v_B:.4f}	{v_out:+.4f} V")
    
    time.sleep(0.5)