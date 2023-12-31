#include <stdio.h>
#include "hangman.h"

void printHangman()
{
    printf(" ___  ___  ________  ________   ________  _____ ______   ________  ________      \n"
           "|\\  \\|\\  \\|\\   __  \\|\\   ___  \\|\\   ____\\|\\   _ \\  _   \\|\\   __  \\|\\   ___  \\    \n"
           "\\ \\  \\\\\\  \\ \\  \\|\\  \\ \\  \\\\ \\  \\ \\  \\___|\\ \\  \\\\\\__\\ \\  \\ \\  \\|\\  \\ \\  \\\\ \\  \\   \n"
           " \\ \\   __  \\ \\   __  \\ \\  \\\\ \\  \\ \\  \\  __\\ \\  \\\\|__| \\  \\ \\   __  \\ \\  \\\\ \\  \\  \n"
           "  \\ \\  \\ \\  \\ \\  \\ \\  \\ \\  \\\\ \\  \\ \\  \\|\\  \\ \\  \\    \\ \\  \\ \\  \\ \\  \\ \\  \\\\ \\  \\ \n"
           "   \\ \\__\\ \\__\\ \\__\\ \\__\\ \\__\\\\ \\__\\ \\_______\\ \\__\\    \\ \\__\\ \\__\\ \\__\\ \\__\\\\ \\__\\\n"
           "    \\|__|\\|__|\\|__|\\|__|\\|__| \\|__|\\|_______|\\|__|     \\|__|\\|__|\\|__|\\|__| \\|__|");
}
void hangMan(int *score)
{
    printHangman();
    printf("\n");
    int salah = 0;
    (*score) = 0;
    char *huruf;
    char *tebakan;
    char *katasudah;
    char *katatebakan;
    int X, i, ctr, benar, gambar, count, addedWordCount = 0;
    Word tertebak;
    Word tebakan1;
    ArrayDin ArrayBlank;
    ArrayDin ArrayKata;
    boolean tidakvalid = true;
    boolean startgame = false;

    ArrayKata = MakeArrayDin();
    STARTWORD("./src/games/hangman/listkata.txt");
    count = WordToInt(currentWord);
    for (i = 0; i < count; i++)
    {
        ADVWORD();
        katatebakan = WordToString(currentWord);
        InsertLast(&ArrayKata, katatebakan);
    }

    ArrayDin ArrayHangman;
    ArrayHangman = MakeArrayDin();
    InsertLast(&ArrayHangman, "\n\n\n\n\n\n___");
    InsertLast(&ArrayHangman, "\n|         \n|         \n|         \n|         \n|         \n|___");
    InsertLast(&ArrayHangman, "_________\n|         \n|         \n|         \n|         \n|         \n|___");
    InsertLast(&ArrayHangman, "_________\n|        | \n|         \n|         \n|         \n|         \n|___");
    InsertLast(&ArrayHangman, "_________\n|        | \n|        O \n|         \n|         \n|         \n|___");
    InsertLast(&ArrayHangman, "_________\n|        | \n|        O \n|        | \n|         \n|         \n|___");
    InsertLast(&ArrayHangman, "_________\n|        | \n|        O \n|        |-- \n|         \n|         \n|___");
    InsertLast(&ArrayHangman, "_________\n|        | \n|        O \n|      --|-- \n|         \n|         \n|___");
    InsertLast(&ArrayHangman, "_________\n|        | \n|        O \n|      --|-- \n|        | \n|         \n|___");
    InsertLast(&ArrayHangman, "_________\n|        | \n|        O \n|      --|-- \n|        | \n|       |  \n|___");
    InsertLast(&ArrayHangman, "_________\n|        | \n|        O \n|      --|-- \n|        | \n|       | | \n|___");

    printf("Hangman telah dimulai! Yuk kita menebak kata!\nDi game ini, kamu harus menebak kata yang berhubungan dengan kehidupan kuliah kita nih!\nBisa saja nama matkul, nama tempat, atau mungkin hal-hal yang kita kerjakan.\nTapi, kamu juga bisa menambahkan kata yang kamu inginkan ke dalam kamus game Hangman ini!\n\n");
    while (tidakvalid)
    {
        printf("*** Menu ***\n");
        printf("1. START GAME\n");
        printf("2. Tambah Kata Baru\n");
        printf("Pilihanmu (Cukup tuliskan angkanya saja): ");
        STARTINPUTKATA();
        printf("\n");
        if (currentWord.Length != 1)
        {
            printf("Maaf, Anda hanya diperbolehkan untuk memasukkan 1 digit angka saja.\n\n");
        }
        else
        {
            int pilihan = WordToInt(currentWord);
            if ((pilihan != 1) && (pilihan != 2))
            {
                printf("Harap masukkan angka 1 atau 2\n\n");
            }
            else if (pilihan == 2)
            {
                tidakvalid = false;
                boolean ingintambah = true;
                while (ingintambah)
                {
                    printf("Masukkan kata baru: ");
                    STARTINPUTKATA();
                    boolean cekangka = true;
                    i = 0;
                    while (cekangka && i < currentWord.Length)
                    {
                        if ((currentWord.TabWord[i] < 65) || ((currentWord.TabWord[i] > 90) && (currentWord.TabWord[i] < 97)) || (currentWord.TabWord[i] > 122))
                        {
                            cekangka = false;
                        }
                        else
                        {
                            i++;
                        }
                    }
                    if (cekangka)
                    {
                        char *katabaru;
                        katabaru = WordToString(currentWord);
                        capsLock(katabaru);
                        while (SearchArrayDin(ArrayKata, katabaru) != -1)
                        {
                            printf("Kata sudah ada di dalam kamus. Silakan masukkan kata lain: ");
                            STARTINPUTKATA();
                            katabaru = WordToString(currentWord);
                            capsLock(katabaru);
                        }
                        InsertLast(&ArrayKata, katabaru);
                        // PrintArrayDin(ArrayKata);
                        addedWordCount++;
                        printf("Kata %s berhasil ditambahkan!\n", katabaru);
                    }
                    else
                    {
                        printf("Maaf, kata yang dimasukkan tidak boleh mengandung karakter selain huruf.\n");
                    }
                    printf("Apakah Anda masih ingin menambah kata baru? (Ya/Tidak)\n");
                    boolean notvalid = true;
                    while (notvalid)
                    {
                        STARTINPUTKATA();
                        if (IsEqual(currentWord, "Tidak"))
                        {
                            ingintambah = false;
                            notvalid = false;
                            startgame = true;
                        }
                        else if (IsEqual(currentWord, "Ya"))
                        {
                            notvalid = false;
                        }
                        else
                        {
                            printf("Mohon masukkan pilihan Ya atau Tidak.\n");
                        }
                    }
                }
            }
            else
            {
                tidakvalid = false;
                startgame = true;
            }
        }
    }
    if (startgame)
    {
        while (salah < 10)
        {
            srand(time(NULL));
            // printf("length array kata: %d\n", LengthArrayDin(ArrayKata));
            X = rand() % LengthArrayDin(ArrayKata);
            tebakan = GetArrayDin(ArrayKata, X);
            tertebak = StringtoWord(tebakan);
            tebakan1 = StringtoWord(tebakan);

            ArrayBlank = MakeArrayDin();
            i = 0;
            ctr = 0;
            while (tebakan[i] != '\0')
            {
                InsertLast(&ArrayBlank, "_ ");
                i++;
            }
            ctr = i;

            Word LetterHistory;
            LetterHistory.Length = 0;
            LetterHistory.TabWord[0] = '-';

            benar = 0;
            gambar = 0;

            while ((salah < 10) && (benar < ctr))
            {
                if (LetterHistory.Length == 0)
                {
                    printf("\nTebakan sebelumnya: %c\n", LetterHistory.TabWord[0]);
                }
                else
                {
                    katasudah = WordToString(LetterHistory);
                    lowerCase(katasudah);
                    printf("\nTebakan sebelumnya: %s\n", katasudah);
                }
                printf("Kata: ");
                PrintArrayDin(ArrayBlank);
                printf("%s\n", GetArrayDin(ArrayHangman, gambar));
                printf("Kesempatan: %d\n", (10 - salah));
                printf("Masukkan tebakan: ");
                STARTINPUTKATA();
                if (currentWord.Length != 1)
                {
                    printf("Maaf, Anda hanya diperbolehkan untuk memasukkan 1 huruf saja.\n");
                }
                else
                {
                    huruf = WordToString(currentWord);
                    capsLock(huruf);
                    if (IsInWord(huruf, tertebak))
                    {
                        for (i = 0; i < ctr; i++)
                        {
                            if (huruf[0] == tebakan[i])
                            {
                                SetArrayDin(&ArrayBlank, i, huruf);
                                tertebak.TabWord[i] = '$';
                                benar++;
                            }
                        }
                        LetterHistory.TabWord[LetterHistory.Length] = huruf[0];
                        LetterHistory.Length++;
                        printf("\n******* Yey! Kamu benar! :D *******\n");
                    }
                    else
                    {
                        if (IsInWord(huruf, LetterHistory))
                        {
                            printf("\n******* Huruf sudah ditebak. *******\n");
                        }
                        else
                        {
                            LetterHistory.TabWord[LetterHistory.Length] = huruf[0];
                            LetterHistory.Length++;
                            salah++;
                            gambar++;
                            printf("\n******* Yahh, kamu salah :( *******\n");
                        }
                    }
                }
            }
            if (benar == ctr)
            {
                printf("\n--- Berhasil menebak kata %s! Kamu mendapatkan %d poin! ---\n", tebakan, benar);
            }
            (*score) += benar;
            DeallocateArrayDin(&ArrayBlank);
        }
        printf("%s\n", GetArrayDin(ArrayHangman, gambar));
        printf("Kesempatan: %d\n", (10 - salah));
        printf("Kata yang benar adalah %s\n\n", tebakan);
        printf("Kesempatan menebakmu telah habis! Permainan berakhir...\n");
        printf("Kamu memperoleh total poin sebesar: %d poin!\n\n", (*score));
        printf("--- GAME OVER ---\n");

        FILE *f;
        f = fopen("./src/games/hangman/listkata.txt", "w+");
        fprintf(f, "%d\n", LengthArrayDin(ArrayKata));
        for (i = 0; i < LengthArrayDin(ArrayKata); i++)
        {
            fprintf(f, "%s\n", GetArrayDin(ArrayKata, i));
        }
        fclose(f);

        DeallocateArrayDin(&ArrayHangman);
        DeallocateArrayDin(&ArrayKata);
    }
}