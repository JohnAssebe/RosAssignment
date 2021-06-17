import numpy as np
def Rx(theta):
    return np.array([
        [1, 0, 0, 0], 
        [0, np.cos(theta), -np.sin(theta), 0], 
        [0, np.sin(theta),np.cos(theta), 0], 
        [ 0,  0,  0,   1]])

def Ry(theta):
    return np.array([
        [np.cos(theta), 0, np.sin(theta), 0], 
        [0, 1, 0, 0], 
        [-np.sin(theta), 0, np.cos(theta), 0],
        [0, 0, 0, 1]])
	
def Rz(theta):
    return np.array([
        [np.cos(theta), np.sin(theta), 0, 0], 
        [np.sin(theta), np.cos(theta), 0, 0], 
        [0, 0, 1 , 0],
        [0, 0, 0, 1]])
	
def T(x=0, y=0, z=0):
    return np.array([[1, 0, 0, x], [0, 1, 0, y], [0, 0, 1, z], [0, 0, 0, 1]])


