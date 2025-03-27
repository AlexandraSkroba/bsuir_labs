import pygame
import random

# Инициализация Pygame
pygame.init()

# Константы
WIDTH, HEIGHT = 800, 600
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
FPS = 60

# Создание окна
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Кот и Бургеры")

# Загрузка изображений
cat_img = pygame.image.load('cat.png')
burger_img = pygame.image.load('burger.png')
pig_img = pygame.image.load('pig.png')

# Масштабирование изображений
cat_img = pygame.transform.scale(cat_img, (50, 50))
burger_img = pygame.transform.scale(burger_img, (30, 30))
pig_img = pygame.transform.scale(pig_img, (60, 60))

# Класс для кота
class Cat:
    def init(self):
        self.image = cat_img
        self.x = WIDTH // 2
        self.y = HEIGHT - 100
        self.width = 50
        self.height = 50
        self.velocity = 5
        self.jump = False
        self.jump_count = 10
        self.strength = 1

    def draw(self, screen):
        screen.blit(self.image, (self.x, self.y))

    def move(self):
        keys = pygame.key.get_pressed()
        if keys[pygame.K_LEFT] and self.x - self.velocity > 0:
            self.x -= self.velocity
        if keys[pygame.K_RIGHT] and self.x + self.velocity < WIDTH - self.width:
            self.x += self.velocity
        if not self.jump:
            if keys[pygame.K_SPACE]:
                self.jump = True
        else:
            if self.jump_count >= -10:
                neg = 1
                if self.jump_count < 0:
                    neg = -1
                self.y -= (self.jump_count ** 2) * 0.5 * neg
                self.jump_count -= 1
            else:
                self.jump = False
                self.jump_count = 10

    def grow(self):
        self.width += 5
        self.height += 5
        self.strength += 1
        self.image = pygame.transform.scale(cat_img, (self.width, self.height))

# Класс для бургера
class Burger:
    def init(self):
        self.image = burger_img
        self.x = random.randint(0, WIDTH - 30)
        self.y = random.randint(0, HEIGHT - 30)

    def draw(self, screen):
        screen.blit(self.image, (self.x, self.y))

# Класс для свинки
class Pig:
    def init(self):
        self.image = pig_img
        self.x = random.randint(0, WIDTH - 60)
        self.y = random.randint(0, HEIGHT - 60)

    def draw(self, screen):
        screen.blit(self.image, (self.x, self.y))

# Основная функция
def main():
    clock = pygame.time.Clock()
    cat = Cat()
    burgers = [Burger() for _ in range(5)]
    pigs = [Pig() for _ in range(3)]
    running = True

    while running:
        clock.tick(FPS)
        screen.fill(WHITE)

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

        cat.move()

        # Проверка на сбор бургеров
        for burger in burgers:
            if cat.x < burger.x + 30 and cat.x + cat.width > burger.x and cat.y < burger.y + 30 and cat.y + cat.height > burger.y:
                burgers.remove(burger)
                cat.grow()

        # Отрисовка объектов
        cat.draw(screen)
        for burger in burgers:
            burger.draw(screen)
        for pig in pigs:
            pig.draw(screen)

        pygame.display.flip()

    pygame.quit()

if __name__ == '__main__':
    main()