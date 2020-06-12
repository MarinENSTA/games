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

FONT = pygame.font.Font("freesansbold.ttf", 100)
WHITE = (255, 255, 255)
BLACK = (0,0,0)

snake=sm.Snake()


def score():
    text_surf = FONT.render(str(snake.length), True, WHITE)
    text_rect = text_surf.get_rect(center=(750/2, 750/2))
    fenetre.blit(text_surf, text_rect)
    
def menu():
    fenetre.fill(BLACK)
    
    speed_surf = FONT.render("Speed", True, WHITE)
    speed_rect = speed_surf.get_rect(center=(750/2, 75))
    fenetre.blit(speed_surf, speed_rect)
    
    slow_surf = FONT.render("slow", True, WHITE)
    slow_rect = slow_surf.get_rect(center=(750/2, 225))
    fenetre.blit(slow_surf, slow_rect)
    
    avg_surf = FONT.render("avg", True, WHITE)
    avg_rect = avg_surf.get_rect(center=(750/2, 375))
    fenetre.blit(avg_surf, avg_rect)
    
    quick_surf = FONT.render("fast", True, WHITE)
    quick_rect = quick_surf.get_rect(center=(750/2, 525))
    fenetre.blit(quick_surf, quick_rect)
    
    torment_surf = FONT.render("Torment XVI", True, WHITE)
    torment_rect = torment_surf.get_rect(center=(750/2, 675))
    fenetre.blit(torment_surf, torment_rect)
    
    pygame.display.flip()
    
    done=False
    
    while not done:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                done = True
            # This block is executed once for each MOUSEBUTTONDOWN event.
            elif event.type == pygame.MOUSEBUTTONDOWN:
                # 1 is the left mouse button, 2 is middle, 3 is right.
                if event.button == 1:
                    # `event.pos` is the mouse position.
                    if slow_rect.collidepoint(event.pos):
                        # Increment the number.
                        speed=200
                        done=True
                    if avg_rect.collidepoint(event.pos):
                        # Increment the number.
                        speed=150
                        done=True
                    if quick_rect.collidepoint(event.pos):
                        # Increment the number.
                        speed=75
                        done=True
                    if torment_rect.collidepoint(event.pos):
                        # Increment the number.
                        speed=20
                        done=True
    return(speed)
                    

speed=menu()
fenetre.blit(background,(0,0))
snake.init_fruit()
snake.display(fenetre,body,fruit)
pygame.display.flip()
continuer=1
success=False
while continuer==1:
    
    if snake.biteself==True:
        pygame.time.wait(speed)
        fenetre.blit(dead, (0,0))
        pygame.display.flip()
        while True :
            for event in pygame.event.get():
                if event.type == QUIT or (event.type == KEYDOWN and event.key == K_ESCAPE):
                    pygame.quit()
                elif event.type == KEYDOWN:
                    pygame.quit()
                    
    elif len(snake.tail)==625:
        pygame.time.wait(speed)
        fenetre.blit(victory, (0,0))
        pygame.display.flip()
        continuer=0
    else:
       # pygame.time.Clock().tick(30)
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
                    score()
                    snake.display(fenetre,body,fruit)
                    pygame.display.flip()
                    pygame.time.wait(speed)
            
            else:
                success=False
    
        if not success:
            snake.auto_dir()
            fenetre.blit(background,(0,0))
            score()
            snake.display(fenetre,body,fruit)
            pygame.display.flip()
            pygame.time.wait(speed)



    

