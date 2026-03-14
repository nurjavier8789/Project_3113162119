import pygame
import sys

pygame.init()

WIDTH = 600
HEIGHT = 400

screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Game Kejar Maling")

WHITE = (255, 255, 255)
BLUE = (0, 195, 255)
RED = (255, 0, 0)

class Character:
    def __init__(self, x, y, color):
        self.x = x
        self.y = y

        self.width = 50
        self.height = 50

        self.speed = 0.5

        self.color = color

    def draw(self, surface):
        pygame.draw.rect(surface, self.color, (self.x, self.y, self.width, self.height))
    
    def get_rect(self):
        return pygame.Rect(self.x, self.y, self.width, self.height)

class Polisi(Character):

    def move(self, keys):
        if keys[pygame.K_LEFT] and self.x > 0:
            self.x -= self.speed
        if keys[pygame.K_RIGHT] and self.x < (pygame.display.Info().current_w - self.width):
            self.x += self.speed
        if keys[pygame.K_UP] and self.y > 0:
            self.y -= self.speed
        if keys[pygame.K_DOWN] and self.y < (pygame.display.Info().current_h - self.height):
            self.y += self.speed

class Maling(Character):

    def move(self, keys):
        if keys[pygame.K_LEFT] and self.x > 0:
            self.x -= self.speed
        if keys[pygame.K_RIGHT] and self.x < (pygame.display.Info().current_w - self.width):
            self.x += self.speed
        if keys[pygame.K_UP] and self.y > 0:
            self.y -= self.speed
        if keys[pygame.K_DOWN] and self.y < (pygame.display.Info().current_h - self.height):
            self.y += self.speed

polisi = Polisi(100, 200, BLUE)
maling = Maling(400, 200, RED)

running = True

while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    keys = pygame.key.get_pressed()

    polisi.move(keys)
    maling.move(keys)

    if polisi.get_rect().colliderect(maling.get_rect()):
        print("Polisi Menang!")
        running = False

    screen.fill(WHITE)

    polisi.draw(screen)
    maling.draw(screen)

    pygame.display.update()

pygame.quit()
sys.exit()
