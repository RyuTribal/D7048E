import pickle
from skl2onnx import convert_sklearn
from skl2onnx.common.data_types import FloatTensorType
import joblib

model = joblib.load('gesture_recognition_model.pkl')

# Define the model's input type; adjust the shape as necessary
# For example, if your input is a vector of 10 floats:
input_type = [('float_input', FloatTensorType([None, 72]))]

# Convert the model
onnx_model = convert_sklearn(model, initial_types=input_type)

# Save the ONNX model
with open("gestures_model.onnx", "wb") as f:
    f.write(onnx_model.SerializeToString())