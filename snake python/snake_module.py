#Classes and methods related to snake game
import pygame
from random import choice
from pygame.locals import *

squaresize=30

class Snake:
    
    def __init__(self):
        # directions : g d h b
        self.dir='droite'
        self.biteself=False
        #level=self.level
        
        #position
        self.x = 3
        self.z = 0
        self.tail=[[3,0],[2,0],[1,0],[0,0]]
        self.length=4
        
        self.fruit_x=0
        self.fruit_z=0
        self.fruit_pos_x=0
        self.fruit_pos_z=0
    
    def auto_dir(self):
        if self.dir == 'bas' :
            self.z+=1
        if self.dir == 'gauche' :
            self.x-=1
        if self.dir == 'haut' :
            self.z-=1
        if self.dir == 'droite' :
            self.x+=1
        self.move()

    def new_dir(self,direction):
        success=False
        
        if direction == 'bas' and self.dir != 'haut' :
            self.z+=1
            self.dir=direction
            success=True
                
        elif direction == 'gauche' and self.dir != 'droite' :
            self.x-=1
            self.dir=direction
            success=True
            
        elif direction == 'haut' and self.dir != 'bas' :
            self.z-=1
            self.dir=direction
            success=True
                
        elif direction == 'droite' and self.dir != 'gauche' :
            self.x+=1
            self.dir=direction
            success=True
        
        if success==True:
            self.move()
        
        return success
        
        
        #print('x : ',self.x)
        #print('z : ',self.z)

    def move(self):
        if self.z==25:
            self.z=0
        elif self.x==-1:
            self.x=24
        elif self.z==-1:
            self.z=24
        elif self.x==25:
            self.x=0
        
        self.tail.insert(0,[self.x,self.z])
        
        if self.tail[0]==[self.fruit_x,self.fruit_z]:
            self.init_fruit()
        elif self.tail[0] in self.tail[1:]:
            self.biteself=True
        else:
            del self.tail[-1]
        
        
    
    def display(self,fenetre,body,fruit):
        for square in self.tail:
            temp_x=square[0]*squaresize
            temp_z=square[1]*squaresize
            fenetre.blit(body, (temp_x,temp_z))
        fenetre.blit(fruit, (self.fruit_x*squaresize,self.fruit_z*squaresize))
            
    def init_fruit(self):
        Sequence=[i for i in range(25)]
        self.fruit_x=choice(Sequence)
        self.fruit_z=choice(Sequence)
        
        while [self.fruit_x,self.fruit_z] in self.tail:
            self.fruit_x=choice(Sequence)
            self.fruit_z=choice(Sequence)
        

    

            
            
        
        
        