import lcm
import time
import numpy as np
from block_goal_msg import block_goal_t

def read_goal(fname):
    transformation = None
    # --- Your code here
    transform = np.eye(4)
    data = np.loadtxt(fname)
    data = data.flatten()
    T = data[0:3]
    R = data[3:12].reshape(3, 3)
    transform[:3, :3] = R
    transform[:3, 3] = T
     # ---

    return transform

def publish_transform(transform):
    # --- Your code here
    lc = lcm.LCM()
    msg = block_goal_t()
    msg.timestamp = int(time.time() * 1e6)
    msg.transform = transform.tolist()
    lc.publish('BLOCK_GOAL', msg.encode())
    # ---

if __name__ == "__main__":
    transform = read_goal('inputs1.txt')
    
    while True:
        publish_transform(transform)
        time.sleep(0.1)
