import pygame
import sys

pygame.init()

WIDTH, HEIGHT = 750, 700
TILE_SIZE = 50
FPS = 60

BG_COLOR = (10, 5, 25)
WALL_COLOR = (40, 40, 100)
ITEM_COLOR = (255, 0, 255)
PLAYER_COLOR = (0, 255, 255)
TEXT_BOX_COLOR = (20, 20, 50)
TERMINAL_COLOR = (255, 255, 0)

try:
    font = pygame.font.Font('monaco.ttf', 30)
except:
    font = pygame.font.Font(None, 30)

screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Betweenspace")
clock = pygame.time.Clock()

class GameObject:
    def __init__(self, x, y, color):
        self.rect = pygame.Rect(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE)
        self.color = color

    def draw(self, surface):
        pygame.draw.rect(surface, self.color, self.rect, border_radius=5)

class Player(GameObject):
    def __init__(self, x, y):
        super().__init__(x, y, PLAYER_COLOR)
        self.inventory = []

    def move(self, dx, dy, walls):
        new_rect = self.rect.copy()
        new_rect.x += dx * TILE_SIZE
        new_rect.y += dy * TILE_SIZE

        # WHAT'S THIS
        collision = False
        for wall in walls:
            if new_rect.colliderect(wall.rect):
                collision = True
                break

        if not collision:
            self.rect = new_rect

class Obstacle(GameObject):
    def __init__(self, x, y):
        super().__init__(x, y, WALL_COLOR)

class Terminal(GameObject):
    def __init__(self, x, y, secret_code):
        super().__init__(x, y, TERMINAL_COLOR)
        self.secret_code = secret_code
        self.is_hacked = False

class NPC(GameObject):
    def __init__(self, x, y, name, dialog_list):
        super().__init__(x, y, ITEM_COLOR)
        self.name = name
        self.dialog_list = dialog_list
        self.dialog_index = 0

    def interact(self):
        if self.dialog_list < len(self.dialog_list):
            text = self.dialog_list[self.dialog_index]
            self.dialog_index += 1
            if self.name == "Asep" and self.dialog_index == len(self.dialog_list):
                pygame.quit()
                sys.exit()
            return f"[{self.name}]: {text}"
        else:
            self.dialog_index = 0
            return ""
        
def main():
    player = Player(1, 1)

    MAZE_MAP = [
        [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],
        [1,0,0,0,1,0,0,0,0,0,0,0,0,0,1],
        [1,0,1,0,1,0,1,1,1,1,1,1,1,0,1],
        [1,0,1,0,0,0,0,0,1,0,0,0,0,0,1],
        [1,0,1,1,1,1,1,0,1,0,1,1,1,1,1],
        [1,0,0,0,0,0,1,0,1,0,0,0,0,0,1],
        [1,1,1,1,1,0,1,0,1,1,1,1,1,0,1],
        [1,0,0,0,1,0,1,0,0,0,0,0,1,0,1],
        [1,0,1,0,1,0,1,1,1,1,1,0,1,0,1],
        [1,0,1,0,0,0,0,0,0,0,0,0,1,0,1],
        [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]
    ]

    walls = []
    for r, row in enumerate(MAZE_MAP):
        for c, tile in enumerate(row):
            if tile == 1: walls.append(Obstacle(c, r))

    gate = Obstacle(10, 5)
    walls.append(gate)

    items = [
        NPC(11, 9, "Blocky", ["Halo! Aku Blocky!!", "Apa?"]),
        NPC(5, 1, "Saturday", ["Whuh!?", "Kok aku disini??", "Tapi jujur, pintu keluarnya tidak terbuka.", "Sekarang apa?"]),
        NPC(5, 5, "Liz", ["Hah...", "Acid...", "Kemana lagi dia kali ini?", "Bikin orang khawatir aja..."]),
        NPC(9, 3, "Penjaga Pintu", ["Aku dengar ada seseorang yang tau clue ini.", "Mungkin explorasi akan membantu."]),
        NPC(1, 9, "???", ["Hai, aku punya kode tapi aku tidak tahu buat apa.", "Kamu mau tau?", "Ini kodenya-", "[ 7 12 9 20 3 8 ]"]),
        NPC(13, 9, "Asep", ["Oh, kamu sudah membuka gerbang!", "Habis itu ngapain?", "Hmm... kurang tau juga sih.", "Ya...", ""])
    ]

    terminal = Terminal(9, 5, "GLITCH")

    current_text = "Gunakan Arrow Keys untuk bergerak, [ENTER] untuk interaksi."
    running = True
    user_input = ""
    is_typing = False

    # WHAT'S THIS
    while running:
        screen.fill(BG_COLOR)

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
            
            if event.type == pygame.KEYDOWN:
                if is_typing:
                    if event.key == pygame.K_RETURN:
                        if user_input.upper() == terminal.secret_code:
                            current_text = ""
                            if gate in walls: walls.remove(gate)
                            terminal.is_hacked = True
                            is_typing = False
                        else:
                            current_text = "KODE SALAH. Coba lagi."
                            is_typing = False
                            user_input = ""
                    elif event.key == pygame.K_ESCAPE:
                        is_typing = False
                        user_input = ""
                        current_text = ""
                    elif event.key == pygame.K_BACKSPACE:
                        user_input = user_input[:-1]
                    else:
                        if len(user_input) < 10:
                            user_input += event.unicode.upper()
                
                else:
                    if event.key == pygame.K_LEFT:  player.move(-1, 0, walls)
                    if event.key == pygame.K_RIGHT: player.move(1, 0, walls)
                    if event.key == pygame.K_UP:    player.move(0, -1, walls)
                    if event.key == pygame.K_DOWN:  player.move(0, 1, walls)

                    if event.key == pygame.K_h: current_text = "Gunakan Arrow Keys untuk bergerak, [ENTER] untuk interaksi."
                    
                    if event.key == pygame.K_RETURN:
                        if player.rect.inflate(20, 20).colliderect(terminal.rect):
                            if not terminal.is_hacked:
                                is_typing = True
                                current_text = "[A1Z26] CODE: "
                            else:
                                current_text = "Terminal sudah diretas."
                        else:
                            for item in items:
                                if player.rect.inflate(20, 20).colliderect(item.rect):
                                    current_text = item.interact()

        for wall in walls: wall.draw(screen)
        for item in items: item.draw(screen)
        terminal.draw(screen)
        player.draw(screen)

        display_msg = current_text + (user_input if is_typing else "")

        if display_msg != "":
            pygame.draw.rect(screen, TEXT_BOX_COLOR, (20, 580, 710, 100), border_radius=10)
            pygame.draw.rect(screen, PLAYER_COLOR, (20, 580, 710, 100), 2, border_radius=10)
            
            display_msg = current_text + (user_input if is_typing else "")
            msg_surf = font.render(display_msg, True, (255, 255, 255))
            screen.blit(msg_surf, (40, 600))

            if is_typing and pygame.time.get_ticks() % 1000 < 500:
                cursor_surf = font.render("_", True, PLAYER_COLOR)
                screen.blit(cursor_surf, (40 + msg_surf.get_width(), 600))

        pygame.display.flip()
        clock.tick(FPS)

if __name__ == "__main__":
    main()
