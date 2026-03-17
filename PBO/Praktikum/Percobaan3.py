import pygame
import sys

pygame.init()

WIDTH = 600
HEIGHT = 400

font = pygame.font.Font(None, 48)
fontHint = pygame.font.Font(None, 24)

screen = pygame.display.set_mode((WIDTH, HEIGHT), pygame.RESIZABLE)
pygame.display.set_caption("Game Kejar Maling")
current_w, current_h = screen.get_size()

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
        if keys[pygame.K_a] and self.x > 0:
            self.x -= self.speed
        if keys[pygame.K_d] and self.x < (pygame.display.Info().current_w - self.width):
            self.x += self.speed
        if keys[pygame.K_w] and self.y > 0:
            self.y -= self.speed
        if keys[pygame.K_s] and self.y < (pygame.display.Info().current_h - self.height):
            self.y += self.speed

polisi = Polisi(400, 200, BLUE)
maling = Maling(100, 200, RED)

running = True
game_over = False
first_move = False

while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    if not game_over:
        keys = pygame.key.get_pressed()

        polisi.move(keys)
        maling.move(keys)

        screen.fill(WHITE)

        polisi.draw(screen)
        maling.draw(screen)

        text_surface = fontHint.render("Polisi: Arrow_up, Arrow_down, Arrow_right, Arrow_left", True, (100, 100, 100))
        text_surface1 = fontHint.render("Maling: W, A, S, D", True, (100, 100, 100))
        screen.blit(text_surface, (25, 25))
        screen.blit(text_surface1, (25, 50))

        if polisi.get_rect().colliderect(maling.get_rect()):
            text_surface = font.render(f"Polisi menang!", True, (0, 0, 0))
            text_rect = text_surface.get_rect(center=(current_w // 2, current_h // 2))

            screen.blit(text_surface, text_rect)
            game_over = True

        pygame.display.update()

pygame.quit()
sys.exit()
