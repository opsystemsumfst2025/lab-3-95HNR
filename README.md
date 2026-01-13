[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/VdiZeKfD)
# 3. Labor — Process Management és IPC

**Környezet:** WSL (Ubuntu/Debian)
**Nyelv:** C
**Téma:** Folyamatok létrehozása, szinkronizációja és kommunikációja

---

## Előkészületek

Mielőtt belevágnánk, telepítsük a szükséges eszközöket WSL-ben:

```bash
sudo apt update
sudo apt install build-essential manpages-dev
```

A `build-essential` tartalmazza a `gcc` fordítót, a `manpages-dev` pedig a rendszerhívások dokumentációját (pl. `man fork`, `man sem_overview`).

---

## Elméleti áttekintés (gyors)

### Mi az a `fork()`?

A `fork()` rendszerhívás **lemásolja** az aktuális folyamatot. Két folyamat lesz belőle:

- **Szülő (Parent)**: az eredeti folyamat
- **Gyermek (Child)**: az új, klónozott folyamat

A kód ugyanaz mindkettőben, de a visszatérési érték alapján tudjuk megkülönböztetni őket:

```c
pid_t pid = fork();

if (pid < 0) {
    // Hiba történt
} else if (pid == 0) {
    // Én vagyok a gyerek
} else {
    // Én vagyok a szülő (pid a gyerek PID-je)
}
```

### Miért kell IPC?

A `fork()` után a gyerek **saját memóriaterületet** kap (copy-on-write). Ha a gyerek átír egy változót, a szülő azt nem látja. Ezért van szükség **Inter-Process Communication** mechanizmusokra (shared memory, pipe, stb.).

---

## Feladatok

### 1. Feladat: A sejtosztódás

**Téma:** `fork()` alapok
📂 Mappa: [`feladat_01/`](feladat_01/)

### 2. Feladat: Zombi-vadászat

**Téma:** `wait()` és a zombie folyamatok
📂 Mappa: [`feladat_02/`](feladat_02/)

### 3. Feladat: Versenyhelyzet

**Téma:** Shared memory és race condition
📂 Mappa: [`feladat_03/`](feladat_03/)

### 4. Feladat: Szinkronizáció

**Téma:** POSIX szemaforok
📂 Mappa: [`feladat_04/`](feladat_04/)

### Házi feladat: Ping-Pong

**Téma:** Folyamatok közötti szigorú sorrendiség
📂 Mappa: [`hazi/`](hazi/)

---

## Gyors fordítás (Makefile)

Ha van `make` telepítve, egyszerűen futtasd:

```bash
make all        # Minden feladat fordítása
make feladat_01 # Csak az első
make clean      # Takarítás
```

Vagy manuálisan is fordíthatsz:

```bash
gcc feladat_01/fork_test.c -o feladat_01/fork_test
```

Szemafor használatához kell a `-pthread` flag:

```bash
gcc feladat_04/shared_mem_sem.c -o feladat_04/shared_mem_sem -pthread
```

---

## Hasznos parancsok

```bash
# Folyamatok listázása
ps aux

# Zombie folyamatok keresése
ps aux | grep Z

# Man oldalak
man fork
man wait
man mmap
man sem_overview
```

---

## Leadandó (egységes)

Kérlek, készíts EGY közös jelentést a repo gyökerében `lab03_jelentes.txt` néven, rövid, tömör pontokban:

- 1. feladat: mit figyeltél meg a `fork()` utáni kimenetek sorrendjéről (1-2 mondat).
- 2. feladat: zombi megfigyelése `wait()` nélkül, majd `wait()`-tel (1-2 mondat).
- 3. feladat: a race condition eredményeinek összefoglalása (néhány szám, 1 mondat magyarázat, hogy a `counter++` nem atomi).
- 4. feladat: szemaforral védett verzió eredménye (várt 200000) és rövid megjegyzés a hatásáról.
- Házi: igazold, hogy a ping-pong váltakozás helyes (1 rövid kimenetrészlet vagy leírás).

Nem kell részletes válaszokat írni, elég rövid megfigyelések és következtetések.

---

**Jó munkát!**
