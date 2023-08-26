# -*- coding: utf-8 -*-
"""Untitled4.ipynb

Automatically generated by Colaboratory.

Original file is located at
    https://colab.research.google.com/drive/1QqV9rTu0k1i0os2hDOMAsyyx8ZXp2DSn
"""

!pip install --upgrade joblib==1.1.0
#downgrade to use mglearn

import matplotlib.pyplot as plt
from sklearn.datasets import fetch_lfw_people
#take dataset
people = fetch_lfw_people(min_faces_per_person=20, resize=0.7)
image_shape = people.images[0].shape

fig, axes =plt.subplots(4,5,figsize=(10,6),subplot_kw={'xticks':(),'yticks':()})
#set print option

for tar, img, ax in zip(people.target, people.images, axes.ravel()):
    ax.imshow(img) 
    ax.set_title(people.target_names[tar])
plt.show()
#print names and picture

import numpy as np

print("people.images.shape : {}".format(people.images.shape))
print("Class : {}".format(len(people.target_names)))
#print image shap and number of class

cnts = np.bincount(people.target)
for i,(cnt,name) in enumerate(zip(cnts,people.target_names)):
    print("{0:30} {1:4}".format(name,cnt))
#print name & count

mask = np.zeros(people.target.shape, dtype=np.bool)
#init make to zero
for target in np.unique(people.target):
    mask[np.where(people.target==target)[0][:20]]=1
#number of target is 20 by person

people_image = people.data[mask]
people_label = people.target[mask]
#take image & label data
people_image = people_image/255
print(people_image.shape)
print(people_label.shape)
#pixel scale control

from sklearn.neighbors import KNeighborsClassifier
from sklearn.model_selection import train_test_split
from sklearn.decomposition import PCA

import matplotlib.pyplot as plt

train1, test1, train2, test2 = train_test_split(people_image,people_label,stratify=people_label, random_state=0)
print(train1.shape)
print(train2.shape)
print(test1.shape)
print(test2.shape)
#divide train/test set

pca = PCA(n_components=100, whiten=True, random_state=0).fit(train1)
pca2 = PCA(n_components=100, whiten=False, random_state=0).fit(train1)

#use PCA model
train1_pca = pca.transform(train1)
train1_pca2 = pca2.transform(train1)

test1_pca = pca.transform(test1)
test1_pca2 = pca2.transform(test1)
#about whitening

plt.figure(1)
plt.scatter(train1[:,0],train1[:,1])
plt.figure(2)
plt.scatter(train1_pca2[:,0],train1_pca2[:,1])
plt.figure(3)
plt.scatter(train1_pca[:,0],train1_pca[:,1])
#print scatter plot about whitening

knn = KNeighborsClassifier(n_neighbors=1)
knn2 = KNeighborsClassifier(n_neighbors=1)

knn.fit(train1_pca, train2)
knn2.fit(train1_pca2, train2)
#fit knn about train data

#use KNN model to learn about whitening
pca0 = PCA(n_components=62, whiten=True, random_state=0).fit(train1)
pca3 = PCA(n_components=10, whiten=True, random_state=0).fit(train1)
pca4 = PCA(n_components=50, whiten=True, random_state=0).fit(train1)
pca5 = PCA(n_components=200, whiten=True, random_state=0).fit(train1)
pca6 = PCA(n_components=500, whiten=True, random_state=0).fit(train1)

train1_pca0 = pca0.transform(train1)
train1_pca3 = pca3.transform(train1)
train1_pca4 = pca4.transform(train1)
train1_pca5 = pca5.transform(train1)
train1_pca6 = pca6.transform(train1)

test1_pca0 = pca0.transform(test1)
test1_pca3 = pca3.transform(test1)
test1_pca4 = pca4.transform(test1)
test1_pca5 = pca5.transform(test1)
test1_pca6 = pca6.transform(test1)

#about number of component
knn0 = KNeighborsClassifier(n_neighbors=1)
knn3 = KNeighborsClassifier(n_neighbors=1)
knn4 = KNeighborsClassifier(n_neighbors=1)
knn5 = KNeighborsClassifier(n_neighbors=1)
knn6 = KNeighborsClassifier(n_neighbors=1)

knn0.fit(train1_pca0, train2)
knn3.fit(train1_pca3, train2)
knn4.fit(train1_pca4, train2)
knn5.fit(train1_pca5, train2)
knn6.fit(train1_pca6, train2)

#use KNN model to learn about whitening
print("accuracy(whitening O) : {:.5f}".format(knn.score(test1_pca,test2)))
print("accuracy(whitening X) : {:.5f}".format(knn2.score(test1_pca2,test2)))
print(" ")
#use KNN model to learn about n_component
print("accuracy(component 62)  : {:.5f}".format(knn0.score(test1_pca0,test2)))
print("accuracy(component 10)  : {:.5f}".format(knn3.score(test1_pca3,test2)))
print("accuracy(component 50)  : {:.5f}".format(knn4.score(test1_pca4,test2)))
print("accuracy(component 10O) : {:.5f}".format(knn.score(test1_pca,test2)))
print("accuracy(component 20O) : {:.5f}".format(knn5.score(test1_pca5,test2)))
print("accuracy(component 50O) : {:.5f}".format(knn6.score(test1_pca6,test2)))

fig, axes = plt.subplots(4, 5, figsize=(10, 8), subplot_kw={'xticks':(), 'yticks':()})
#print option set
for i, (component, ax) in enumerate(zip(pca.components_, axes.ravel())):
    ax.imshow(component.reshape(image_shape), cmap='viridis') 
    ax.set_title("component {}".format(i + 1))
plt.show()
#print components

from sklearn.preprocessing import MinMaxScaler

train1, test1, train2, test2 = train_test_split(MinMaxScaler().fit_transform(people_image),people_label,stratify=people_label, random_state=0)
print(train1.shape)
print(train2.shape)
print(test1.shape)
print(test2.shape)
#divide train/test set

pca = PCA(n_components=100, whiten=True, random_state=0).fit(train1)
pca2 = PCA(n_components=100, whiten=False, random_state=0).fit(train1)

#use PCA model
train1_pca = pca.transform(train1)
train1_pca2 = pca2.transform(train1)

test1_pca = pca.transform(test1)
test1_pca2 = pca2.transform(test1)
#about whitening

plt.figure(1)
plt.scatter(train1[:,0],train1[:,1])
plt.figure(2)
plt.scatter(train1_pca2[:,0],train1_pca2[:,1])
plt.figure(3)
plt.scatter(train1_pca[:,0],train1_pca[:,1])
#print scatter plot about whitening

knn = KNeighborsClassifier(n_neighbors=1)
knn2 = KNeighborsClassifier(n_neighbors=1)

knn.fit(train1_pca, train2)
knn2.fit(train1_pca2, train2)
#fit knn about train data

#use KNN model to learn about whitening
pca0 = PCA(n_components=62, whiten=True, random_state=0).fit(train1)
pca3 = PCA(n_components=10, whiten=True, random_state=0).fit(train1)
pca4 = PCA(n_components=50, whiten=True, random_state=0).fit(train1)
pca5 = PCA(n_components=200, whiten=True, random_state=0).fit(train1)
pca6 = PCA(n_components=500, whiten=True, random_state=0).fit(train1)

train1_pca0 = pca0.transform(train1)
train1_pca3 = pca3.transform(train1)
train1_pca4 = pca4.transform(train1)
train1_pca5 = pca5.transform(train1)
train1_pca6 = pca6.transform(train1)

test1_pca0 = pca0.transform(test1)
test1_pca3 = pca3.transform(test1)
test1_pca4 = pca4.transform(test1)
test1_pca5 = pca5.transform(test1)
test1_pca6 = pca6.transform(test1)

#about number of component
knn0 = KNeighborsClassifier(n_neighbors=1)
knn3 = KNeighborsClassifier(n_neighbors=1)
knn4 = KNeighborsClassifier(n_neighbors=1)
knn5 = KNeighborsClassifier(n_neighbors=1)
knn6 = KNeighborsClassifier(n_neighbors=1)

knn0.fit(train1_pca0, train2)
knn3.fit(train1_pca3, train2)
knn4.fit(train1_pca4, train2)
knn5.fit(train1_pca5, train2)
knn6.fit(train1_pca6, train2)

#use KNN model to learn about whitening
print("accuracy(whitening O) : {:.5f}".format(knn.score(test1_pca,test2)))
print("accuracy(whitening X) : {:.5f}".format(knn2.score(test1_pca2,test2)))
print(" ")
#use KNN model to learn about n_component
print("accuracy(component 62)  : {:.5f}".format(knn0.score(test1_pca0,test2)))
print("accuracy(component 10)  : {:.5f}".format(knn3.score(test1_pca3,test2)))
print("accuracy(component 50)  : {:.5f}".format(knn4.score(test1_pca4,test2)))
print("accuracy(component 10O) : {:.5f}".format(knn.score(test1_pca,test2)))
print("accuracy(component 20O) : {:.5f}".format(knn5.score(test1_pca5,test2)))
print("accuracy(component 50O) : {:.5f}".format(knn6.score(test1_pca6,test2)))

fig, axes = plt.subplots(4, 5, figsize=(10, 8), subplot_kw={'xticks':(), 'yticks':()})
#print option set
for i, (component, ax) in enumerate(zip(pca.components_, axes.ravel())):
    ax.imshow(component.reshape(image_shape), cmap='viridis') 
    ax.set_title("component {}".format(i + 1))
plt.show()
#print components

#fig2, axes2 = plt.subplots(4, 5, figsize=(10, 8), subplot_kw={'xticks':(), 'yticks':()})

train_re = pca.inverse_transform(train1_pca)
test_re = pca.inverse_transform(test1_pca)

train_re3 = pca3.inverse_transform(train1_pca3)
test_re3 = pca3.inverse_transform(test1_pca3)

train_re4 = pca4.inverse_transform(train1_pca4)
test_re4 = pca4.inverse_transform(test1_pca4)

train_re6 = pca6.inverse_transform(train1_pca6)
test_re6 = pca6.inverse_transform(test1_pca6)

plt.imshow(train1[0].reshape(image_shape))
plt.figure(figsize = (10,8))
plt.subplot(1,4,1)
plt.imshow(train_re3[0].reshape(image_shape))
plt.axis('off')
plt.subplot(1,4,2)
plt.imshow(train_re4[0].reshape(image_shape))
plt.axis('off')
plt.subplot(1,4,3)
plt.imshow(train_re[0].reshape(image_shape))
plt.axis('off')
plt.subplot(1,4,4)
plt.imshow(train_re6[0].reshape(image_shape))
plt.axis('off')
plt.show

!pip install mglearn

import mglearn

mglearn.plots.plot_pca_faces(train1, test1, image_shape)
#reconstruction photo

import tensorflow as tf
import keras
from keras.models import Sequential
from keras.layers import Dense, Dropout, Flatten
from keras.layers.convolutional import Conv2D, MaxPooling2D

from keras.utils import to_categorical
from sklearn.preprocessing import MinMaxScaler
#import to make CNN model

train1_cnn, test1_cnn, train2_cnn, test2_cnn = train_test_split(MinMaxScaler().fit_transform(people_image),people_label, stratify=people_label,random_state=0)
#set cnn train/test data based original data

train2_cnn = to_categorical(train2_cnn, num_classes=62)
test2_cnn = to_categorical(test2_cnn, num_classes=62)

train1_cnn =train1_cnn.reshape(train1_cnn.shape[0],87,65)
test1_cnn =test1_cnn.reshape(test1_cnn.shape[0],87,65)
#reshape data to put in CNN

print(train1_cnn.shape)
print(test1_cnn.shape)

print(train2_cnn.shape)
print(test2_cnn.shape)

model = Sequential()
model.add(Conv2D(32, kernel_size=5, padding='same', input_shape=(87, 65, 1), activation='relu'))
model.add(MaxPooling2D(2,2))
model.add(Conv2D(64, kernel_size=2, padding='same', activation='relu'))
model.add(MaxPooling2D(2,2))
model.add(Dropout(0.25))
model.add(Flatten())
model.add(Dense(32, activation='relu'))
model.add(Dropout(0.25))
model.add(Dense(62, activation='softmax'))

model.summary()

batch_size = 4
epochs = 20
model.compile(loss='categorical_crossentropy', optimizer='adam', metrics=['accuracy'])
hist = model.fit(train1_cnn, train2_cnn, batch_size=batch_size, epochs=epochs, verbose=1)

score = model.evaluate(test1_cnn, test2_cnn, verbose=0)

print('Test loss:', score[0])
print('Test accuracy', score[1])
