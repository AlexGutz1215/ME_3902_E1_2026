import machine
import time
import ustruct

i2c = machine.I2C(0, scl=machine.Pin(5), sda=machine.Pin(4), freq = 400000)
ADS_ADDR = 0x48

POINTER_CONVERSION = 0x00
POINTER_CONFIG = 0x01

CONFIG_DIFF_A0_A1_4_096V = 0x0284
LSB_SIZE = 4.096 / 32768

def init_ads1115():
    config_bytes = ustruct.pack('>H', CONFIG_DIFF_A0_A1_4_096V)
    i2c.writeto_mem(ADS_ADDR, POINTER_CONFIG, config_bytes)
    
def read_differential_voltage():
    data = i2c.readfrom_mem(ADS_ADDR, POINTER_CONVERSION, 2)
    raw_value = ustruct.unpack('>h', data)[0]
    return raw_value * LSB_SIZE

V_EXCITATION = 3.3
GAUGE_FACTOR = 2.09

init_ads1115()
time.sleep(0.1)

print("Calibrating baseline... Keep ruler completely still.")
v_tare = sum([read_differential_voltage() for _ in range(50)]) / 50
print(f"Tare Offset Established: {v_tare:+.6f} V\n")

print(f"{'Raw Delta V (mV)': <20}{'Calculated Mircostrain (ue)':<25}")

while True:
    v_diff = (sum([read_differential_voltage() for _ in range(20)]) / 20) - v_tare
    
    strain = (4.0 * v_diff) / (GAUGE_FACTOR * V_EXCITATION)
    microstrain = strain * 1e6
    
    print(f"{v_diff * 1000:+.4f} mv			{microstrain:+.2f} ue")
    time.sleep(0.2)