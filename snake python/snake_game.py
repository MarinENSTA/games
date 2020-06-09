#Project's main

import pygame
from pygame.locals import *

import snake_module as sm
from random import choice

pygame.init()

#Ouverture de la fenêtre Pygame (carré : largeur = hauteur)
fenetre = pygame.display.set_mode((750,750))
#Icone
icone = pygame.image.load("images/snake_icon.png")
pygame.display.set_icon(icone)
#Titre
pygame.display.set_caption("Snake")

background=pygame.image.load('images/background_square.png').convert()
body = pygame.image.load('images/snake_square.png').convert()
fruit=pygame.image.load('images/red_square.png').convert()
dead=pygame.image.load('images/game_over.jpg').convert()
victory=pygame.image.load('images/victory.png').convert()

squaresize=30

snake=sm.Snake()

fenetre.blit(background,(0,0))
snake.init_fruit()
snake.display(fenetre,body,fruit)


pygame.display.flip()
continuer=1
while continuer==1:
    
    if snake.biteself==True:
        pygame.time.wait(50)
        fenetre.blit(dead, (0,0))
        pygame.display.flip()
        continuer=0
    elif len(snake.tail)==625:
        pygame.time.wait(50)
        fenetre.blit(victory, (0,0))
        pygame.display.flip()
        continuer=0
    else:
        pygame.time.Clock().tick(30)
        for event in pygame.event.get():
            if event.type == QUIT or (event.type == KEYDOWN and event.key == K_ESCAPE):
                pygame.quit()
                
            elif event.type == KEYDOWN:
                if event.key == K_d:
                    success=snake.new_dir('droite')
                elif event.key == K_a:
                    success=snake.new_dir('gauche')
                elif event.key == K_w:
                    success=snake.new_dir('haut')
                elif event.key == K_s:
                    success=snake.new_dir('bas')
                
                if success:
                    fenetre.blit(background,(0,0))
                    snake.display(fenetre,body,fruit)
                    pygame.display.flip()
                    pygame.time.wait(100)
            
            else:
                success=False
    
        if not success:
            snake.auto_dir()
            fenetre.blit(background,(0,0))
            snake.display(fenetre,body,fruit)
            pygame.display.flip()
            pygame.time.wait(100)
    
    


    

