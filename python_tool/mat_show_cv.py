import cv2
import matplotlib.pyplot as plt

img = cv2.imread("sample_dog.jpg")
plt.subplot(121)
plt.imshow(img)

# convert BGR to RGB
img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
plt.subplot(122)
plt.imshow(img)
plt.show()