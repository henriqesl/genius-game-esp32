## 🎮 Genius Game com ESP32

Este é um projeto de jogo estilo "Genius", _famoso jogo da memória_ desenvolvido com o microcontrolador **ESP32**, utilizando LEDs, botões, buzzer e display OLED. O objetivo é testar a memória do jogador através da repetição de sequências de cores e sons.

- O jogo sorteia uma sequência de cores (representadas por LEDs).
- A cada rodada, a sequência aumenta em 1.
- O jogador deve repetir corretamente a sequência para avançar.
- Se errar, o jogo termina.
- O jogo possui **3 níveis de dificuldade**, que alteram a velocidade da sequência:
  - **Fácil (verde)**
  - **Médio (amarelo)**
  - **Difícil (vermelho)**

---

### 📂 Código

- `setup()` – Inicializa os pinos, display e gera a sequência.
- `loop()` – Controla os estados do jogo (início, seleção de dificuldade, exibição da sequência, turno do jogador, fim do jogo e vitória).
- Funções auxiliares:
  - `generateSequence()`
  - `showWelcome()`
  - `selectDifficulty()`
  - `showSequence()`
  - `handlePlayerInput()`
  - `displayGameOver()`
  - `displaySuccess()`
  - `resetGame()`

---

### 🚀 Como Jogar?

1. Conecte os componentes ao ESP32 conforme os pinos definidos no código.
2. Carregue o código usando o Arduino IDE ou PlatformIO.
3. Abra o monitor serial (opcional) para ver logs.
4. Escolha a dificuldade pressionando um dos botões:
   - Verde = Fácil
   - Amarelo = Médio
   - Vermelho = Difícil
5. Siga as sequências corretamente e avance até o fim!

### 💻 Autor

**Henrique Silva**  
Estudante de Sistemas de Informação / Técnico em Eletrônica  
📍 Recife - PE  
🔗 [LinkedIn](https://www.linkedin.com/in/henrique-silva-b8583932a/)

---

Este projeto é livre para uso educacional. Sinta-se à vontade para estudar, modificar e compartilhar!

https://private-user-images.githubusercontent.com/163488602/435034417-96c6732a-5cd6-4efa-9f66-83c2beeea798.mp4?jwt=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJnaXRodWIuY29tIiwiYXVkIjoicmF3LmdpdGh1YnVzZXJjb250ZW50LmNvbSIsImtleSI6ImtleTUiLCJleHAiOjE3NDQ5NTEyMDYsIm5iZiI6MTc0NDk1MDkwNiwicGF0aCI6Ii8xNjM0ODg2MDIvNDM1MDM0NDE3LTk2YzY3MzJhLTVjZDYtNGVmYS05ZjY2LTgzYzJiZWVlYTc5OC5tcDQ_WC1BbXotQWxnb3JpdGhtPUFXUzQtSE1BQy1TSEEyNTYmWC1BbXotQ3JlZGVudGlhbD1BS0lBVkNPRFlMU0E1M1BRSzRaQSUyRjIwMjUwNDE4JTJGdXMtZWFzdC0xJTJGczMlMkZhd3M0X3JlcXVlc3QmWC1BbXotRGF0ZT0yMDI1MDQxOFQwNDM1MDZaJlgtQW16LUV4cGlyZXM9MzAwJlgtQW16LVNpZ25hdHVyZT02YTRhM2IyZmVjYTAwZDNlZjIzYjc1NDA5NDEyMWExMmUzMDE1MzllMGJiZWZjYmYyNjk0NjNlZjMxZTRkYjFkJlgtQW16LVNpZ25lZEhlYWRlcnM9aG9zdCJ9.zlG6HfvM_T7j5pDkJzfCQKZa-DAHVuL2J4ANfxve_BY
