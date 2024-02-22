import os
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.multiclass import OneVsRestClassifier
from sklearn.svm import SVC
from sklearn.pipeline import make_pipeline
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import accuracy_score, confusion_matrix
import joblib
import matplotlib.pyplot as plt
import seaborn as sns

# Definition of directories containing data files
train_dir = "App/Database"

test=False

# Initialization of lists to store data and labels
x_train = []  # The training data
y_train = []  # The training labels (gestures)
x_test = []  # The test data
y_test = []  # The test labels (gestures)

NB_PERSON = 10
WINDOWS_SIZE = 100
# Load training data
for person in range(1, NB_PERSON+1):
    if(person>NB_PERSON*0.6): test=True
    for gesture in range(6, 12):
        for repetition in range(1, 6):
            filename = f"S{person}_G{gesture}_R{repetition}.txt"
            filepath = os.path.join(train_dir, filename)
            if os.path.exists(filepath):  # Check if the file exists
                print(filename)
                with open(filepath, "r") as file:
                    # Read lines from the file
                    data = file.readlines()

                    # Initialization of lists to store coordinates of each finger and the hand
                    thumb_positions = []
                    index_positions = []
                    middle_positions = []
                    ring_positions = []
                    pinky_positions = []
                    palm_positions = []
                    #left_hand = []
                    
                    # Initialization of lists to store features of each time window
                    thumb = []
                    index = []
                    middle = []
                    ring = []
                    pinky = []

                    # Initialization of the time window
                    window_size = WINDOWS_SIZE
                    index = 0

                    try:
                        # Traverse the lines of the file
                        for line in data:
                            if line.startswith(" ,hand_Id_type:"):
                                #if "Left" in line: left_hand.append(1)
                                #else: left_hand.append(0)
                                palm_positions.append([float(x) for x in line.split('(')[2].split(')')[0].split(',')])
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
                                #left_hand = int(np.median(left_hand))
                                palm = [np.mean(palm_positions, axis=0), np.std(palm_positions, axis=0), np.cov(palm_positions, rowvar=False).diagonal(), np.sqrt(np.mean(np.square(palm_positions), axis=0))]
                                thumb = [np.mean(thumb_positions, axis=0), np.std(thumb_positions, axis=0), np.cov(thumb_positions, rowvar=False).diagonal(), np.sqrt(np.mean(np.square(thumb_positions), axis=0))]
                                index = [np.mean(index_positions, axis=0), np.std(index_positions, axis=0), np.cov(index_positions, rowvar=False).diagonal(), np.sqrt(np.mean(np.square(index_positions), axis=0))]
                                middle = [np.mean(middle_positions, axis=0), np.std(middle_positions, axis=0), np.cov(middle_positions, rowvar=False).diagonal(), np.sqrt(np.mean(np.square(middle_positions), axis=0))]
                                ring = [np.mean(ring_positions, axis=0), np.std(ring_positions, axis=0), np.cov(ring_positions, rowvar=False).diagonal(), np.sqrt(np.mean(np.square(ring_positions), axis=0))]
                                pinky = [np.mean(pinky_positions, axis=0), np.std(pinky_positions, axis=0), np.cov(pinky_positions, rowvar=False).diagonal(), np.sqrt(np.mean(np.square(pinky_positions), axis=0))]

                                #print(palm)

                                # Concatenation of finger position lists and palm position, palm normal, and hand direction
                                features = np.concatenate([palm, thumb, index, middle, ring, pinky]).flatten()
                                #features = np.concatenate([[left_hand], features])

                                # Add features and label to x and y
                                if(test):
                                    x_test.append(features)
                                    y_test.append(gesture)
                                else:
                                    x_train.append(features)
                                    y_train.append(gesture)  # Assuming the label is the gesture number

                                #left_hand = []
                                palm_positions = []
                                thumb_positions = []
                                index_positions = []
                                middle_positions = []
                                ring_positions = []
                                pinky_positions = []
                                index = 0
                    except:
                        print("Error on file: ", filename)
            else: print("Missing file ", filename)

# Convert lists to numpy arrays
x_train = np.array(x_train)
y_train = np.array(y_train)
x_test = np.array(x_test)
y_test = np.array(y_test)

# Create a pipeline with a scaler and an SVM classifier
clf = make_pipeline(StandardScaler(), OneVsRestClassifier(SVC(kernel='rbf', probability=True)))

# Train the model
print("Training the model...")
clf.fit(x_train, y_train)

# Predict on the test set
print("Testing the model...")
y_pred = clf.predict(x_test)

# Calculate the accuracy of the model
accuracy = accuracy_score(y_test, y_pred)
print("Accuracy:", accuracy)

# Calculate the confusion matrix
conf_matrix = confusion_matrix(y_test, y_pred)

# Calculate the total number of observations for each class
class_totals = np.sum(conf_matrix, axis=1)

# Divide each element of the confusion matrix by the total number of observations for that class
conf_matrix_percent = 100 * conf_matrix / class_totals[:, None]

# Plot the confusion matrix
plt.figure(figsize=(10, 8))
sns.heatmap(conf_matrix_percent, annot=True, cmap='Blues', fmt='0.1f')
plt.xlabel('Predicted')
plt.ylabel('Actual')
plt.title('Confusion Matrix')
plt.savefig('App/src/confusion_matrix.png')
plt.show()

# Export the trained model
joblib.dump(clf, 'App/src/gesture_recognition_model.pkl')
