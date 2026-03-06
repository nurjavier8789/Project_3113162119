import pygame
import sys

pygame.init()

WIDTH = 600
HEIGHT = 400

font = pygame.font.Font(None, 48)
last_key = ""

screen = pygame.display.set_mode((WIDTH, HEIGHT), pygame.RESIZABLE)
pygame.display.set_caption("Praktikum PBO - Pygame")

WHITE = (255, 255, 255)
RED = (255, 0, 0)
GREEN = (0, 255, 0)
BLUE = (0, 195, 255)

class Player:
    def __init__(self, x, y):
        self.x = x
        self.y = y

        self.width = 50
        self.height = 50

        self.speed = 0.5

        self.color = WHITE

    def move(self, keys):
        if keys[pygame.K_LEFT] and self.x > 0:
            self.x -= self.speed
        if keys[pygame.K_RIGHT] and self.x < (pygame.display.Info().current_w - self.width):
            self.x += self.speed
        if keys[pygame.K_UP] and self.y > 0:
            self.y -= self.speed
        if keys[pygame.K_DOWN] and self.y < (pygame.display.Info().current_h - self.height):
            self.y += self.speed

    def draw(self, surface):
        pygame.draw.rect(surface, self.color, (self.x, self.y, self.width, self.height))

    def change_color(self, keys):
        if keys[pygame.K_1] or keys[pygame.K_KP1]:
            self.color = RED
        if keys[pygame.K_2] or keys[pygame.K_KP2]:
            self.color = WHITE

    def change_size(self, keys):
        if keys[pygame.K_p]:
            if self.height < (pygame.display.Info().current_h - self.y) and self.width < (pygame.display.Info().current_w - self.x):
                self.height += 0.2
                self.width += 0.2
        if keys[pygame.K_o]:
            if self.height > 10 and self.width > 10:
                self.height -= 0.2
                self.width -= 0.2

    def change_speed(self, keys):
        if keys[pygame.K_8]:
            self.speed = 1
        if keys[pygame.K_9]:
            self.speed = 2
        if keys[pygame.K_0]:
            self.speed = 0.5

player = Player(300, 200)

running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

        if event.type == pygame.KEYDOWN:
            last_key = pygame.key.name(event.key)

        if event.type == pygame.KEYUP:
            pass

    keys = pygame.key.get_pressed()

    player.move(keys)
    player.change_color(keys)
    player.change_size(keys)
    player.change_speed(keys) # Showcase Purpose

    screen.fill(BLUE)

    # Showcase Purpose
    text_surface = font.render(f"Last key: {last_key}", True, (0, 0, 0))
    text_surface2 = font.render(f"Current speed: {player.speed}", True, (0, 0, 0))
    screen.blit(text_surface, (25, 25))
    screen.blit(text_surface2, (pygame.display.Info().current_w - 320, pygame.display.Info().current_h - 50))
    # Showcase Purpose

    player.draw(screen)
    pygame.display.flip()

pygame.quit()
sys.exit()
