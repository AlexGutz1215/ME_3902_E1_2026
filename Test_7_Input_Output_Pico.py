from machine import ADC, Pin, PWM
import time

fsr=ADC(Pin(26))

VCC=3.3

Resistance = 10000.0

# print("Calibration step...")
# time.sleep(1)

servo = PWM(Pin(15))
servo.freq(50)

while True:

    adc_val = fsr.read_u16() >> 4
    
    if adc_val > 30:
    
        v_out = (adc_val * VCC) / 4095.0
        
        if v_out <=0:
            v_out=0.001
    
        resistance_fsr = Resistance * ((VCC/v_out) - 1.0)
        
        if resistance_fsr <=0:
            resitance_fsr=0.01
    
        conductance = 1000000.0/resistance_fsr
        
        if conductance < 100:
            
            angle = 45
            duty = int(1638 + (angle / 180.0) * (8192 - 1638))
            servo.duty_u16(duty)
        elif conductance<500:
           angle=90
           duty = int(1638 + (angle / 180.0) * (8192 - 1638))
           servo.duty_u16(duty)
    
        # print(f"ADC Value: {adc_val} | Conductance:{conductance:.2f} uS")
    
    else:
        
        # print("ADC Value: 0 | Conductance: 0.00 uS")
        
        print("No finger press, henco servo is not acuated")
    
    time.sleep(1)
