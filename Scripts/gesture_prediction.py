import os
import numpy as np
import joblib
import sys

# Load the trained model
clf = joblib.load('gesture_recognition_model.pkl')

# Get the filename and window size from the command line arguments
if len(sys.argv) < 3:
    print("Usage: python gesture_prediction.py <filename> <window_size>")
    sys.exit(1)

filename = sys.argv[1]
window_size = int(sys.argv[2])

if os.path.exists(filename):  # Check if the file exists
    with open(filename, "r") as file:
        # Read lines from the file
        data = file.readlines()

        # Initialization of lists to store coordinates of each finger and the hand
        thumb_positions = []
        index_positions = []
        middle_positions = []
        ring_positions = []
        pinky_positions = []
        palm_positions = []
        palm_normals = []
        hand_directions = []
        left_hand = []

        # Initialization of lists to store features of each time window
        thumb = []
        index = []
        middle = []
        ring = []
        pinky = []

        # Initialization of the time window
        index = 0

        # Traverse the lines of the file
        for line in data:
            if line.startswith(" ,hand_Id_type:"):
                if "Left" in line: left_hand.append(1)
                else: left_hand.append(0)
                hand_directions.append([float(x) for x in line.split('(')[1].split(')')[0].split(',')])
                palm_positions.append([float(x) for x in line.split('(')[2].split(')')[0].split(',')])
                palm_normals.append([float(x) for x in line.split('(')[3].split(')')[0].split(',')])
            elif line.startswith(" ,Finger_type(tipposition) TYPE_THUMB"):
                thumb_positions.append([float(x) for x in line.split('(')[2].split(')')[0].split(',')])
            elif line.startswith(" ,Finger_type(tipposition) TYPE_INDEX"):
                index_positions.append([float(x) for x in line.split('(')[2].split(')')[0].split(',')])
            elif line.startswith(" ,Finger_type(tipposition) TYPE_MIDDLE"):
                middle_positions.append([float(x) for x in line.split('(')[2].split(')')[0].split(',')])
            elif line.startswith(" ,Finger_type(tipposition) TYPE_RING"):
                ring_positions.append([float(x) for x in line.split('(')[2].split(')')[0].split(',')])
            elif line.startswith(" ,Finger_type(tipposition) TYPE_PINKY"):
                pinky_positions.append([float(x) for x in line.split('(')[2].split(')')[0].split(',')])
                index += 1

                # If the time window is full, calculate the features and reset the window
            if index == window_size:
                #print(palm_positions)
                left_hand = int(np.median(left_hand))
                hand_dir = [np.mean(hand_directions, axis=0), np.std(hand_directions, axis=0), np.cov(hand_directions, rowvar=False).diagonal(), np.sqrt(np.mean(np.square(hand_directions), axis=0))]
                palm_pos = [np.mean(palm_positions, axis=0), np.std(palm_positions, axis=0), np.cov(palm_positions, rowvar=False).diagonal(), np.sqrt(np.mean(np.square(palm_positions), axis=0))]
                palm_norm = [np.mean(palm_normals, axis=0), np.std(palm_normals, axis=0), np.cov(palm_normals, rowvar=False).diagonal(), np.sqrt(np.mean(np.square(palm_normals), axis=0))]
                thumb = [np.mean(thumb_positions, axis=0), np.std(thumb_positions, axis=0), np.cov(thumb_positions, rowvar=False).diagonal(), np.sqrt(np.mean(np.square(thumb_positions), axis=0))]
                index = [np.mean(index_positions, axis=0), np.std(index_positions, axis=0), np.cov(index_positions, rowvar=False).diagonal(), np.sqrt(np.mean(np.square(index_positions), axis=0))]
                middle = [np.mean(middle_positions, axis=0), np.std(middle_positions, axis=0), np.cov(middle_positions, rowvar=False).diagonal(), np.sqrt(np.mean(np.square(middle_positions), axis=0))]
                ring = [np.mean(ring_positions, axis=0), np.std(ring_positions, axis=0), np.cov(ring_positions, rowvar=False).diagonal(), np.sqrt(np.mean(np.square(ring_positions), axis=0))]
                pinky = [np.mean(pinky_positions, axis=0), np.std(pinky_positions, axis=0), np.cov(pinky_positions, rowvar=False).diagonal(), np.sqrt(np.mean(np.square(pinky_positions), axis=0))]

                #print(palm)

                # Concatenation of finger position lists and palm position, palm normal, and hand direction
                features = np.concatenate([hand_dir, palm_pos, palm_norm, thumb, index, middle, ring, pinky]).flatten()
                features = np.concatenate([[left_hand], features])

                # Predict the gesture using the trained model
                gesture = clf.predict([features])[0]
                #print("Predicted gesture:", gesture)

                # Get the confidence of the prediction
                confidence = max(clf.predict_proba([features])[0])
                #print("Confidence:", confidence)
                if(confidence<0.2): print("I don't know, I'll say gesture ", gesture)
                elif(confidence<0.6): print("Maybe gesture ", gesture)
                elif(confidence<0.85): print("Pretty sure it's gesture ", gesture)
                else: print("Gesture ", gesture)

                left_hand = []
                hand_directions = []
                palm_positions = []
                palm_normals = []
                thumb_positions = []
                index_positions = []
                middle_positions = []
                ring_positions = []
                pinky_positions = []
                index = 0

else:
    print("File not found:", filename)
