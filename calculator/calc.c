#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define MAX 100

// ฟังก์ชันตรวจสอบตัวเลข
double readFactor(char **p){
    // เตรียมตัวชี้สำหรับการบอกจุดสิ้นสุดตัวเลข
    char *end_ptr;

    //เอาตำแหน่งหลังจากจบตัวเลข ไปใส่ไว้ใน end_ptr
    double num = strtod(*p, &end_ptr);
    // ตรวจสอบว่ามีการอ่านตัวเลขจริงไหม (ถ้า end_ptr ขยับ แปลว่าอ่านได้)
    if (*p != end_ptr) {
        // อัปเดตตำแหน่ง pointer หลักของเรา ให้ไปอยู่ที่เดียวกับ end_ptr
        // (คือข้ามตัวเลขที่อ่านไปแล้ว)
        *p = end_ptr;
    }
    
    return num;

}

void deleteElement(double nums[], char ops[], int index, int *count) {
    for (int i = index + 1; i < *count; i++) {
        nums[i] = nums[i + 1] ;
    }
    for (int i = index; i < *count - 1; i++) {
        ops[i] = ops[i + 1] ;
    }
    (*count)-- ;
}//calculation function


void process(double nums[], char ops[], int *count, const char *validOps) {
    int i = 0 ;
    
    while (i < *count - 1) {
        char currentOp = ops[i];

        if (strchr(validOps, currentOp) != NULL) {
            double val1 = nums[i] ;
            double val2 = nums[i+1] ;
            double res = 0 ;

            
            if (currentOp == '*') res = val1 * val2 ;
            else if (currentOp == '/') res = (val2 != 0) ? val1 / val2 : 0 ;
            else if (currentOp == '%') res = (int)val1 % (int)val2 ;
            else if (currentOp == '+') res = val1 + val2 ;
            else if (currentOp == '-') res = val1 - val2 ;

            nums[i] = res ; 
            deleteElement(nums, ops, i, count) ; 
            
        } else {
            i++ ; 
        }
    }
}
int main() {
    // 1. เตรียมข้อมูล
    char input[MAX];
    printf("Enter expression: ");
    fgets(input, MAX, stdin); // รับค่าจากคีย์บอร์ด

    double nums[MAX]; // เก็บตัวเลข
    char ops[MAX];    // เก็บเครื่องหมาย
    int count = 0;    // นับจำนวนตัวเลข
    
    char *p = input;

    // 2. ลูปอ่านค่า (ใช้ฟังก์ชันของคุณ + เก็บลง array)
    while (*p != '\0' && *p != '\n') {

        // 2.1 อ่านตัวเลขด้วยฟังก์ชันของคุณ
        nums[count] = readFactor(&p);
        count++;

        // 2.2 ข้ามช่องว่าง (ถ้ามี) เพื่อไปหาเครื่องหมาย
        while (*p == ' ') 
        p++;

        // 2.3 เช็คว่าจบประโยคหรือยัง
        if (*p == '\0' || *p == '\n') 
        break;

        // 2.4 อ่านเครื่องหมาย (Operator)
        ops[count - 1] = *p; // เก็บเครื่องหมาย (index ของ ops จะตามหลัง nums อยู่ 1)
        p++; // ขยับข้ามเครื่องหมายไป
    }

    // 3. เริ่มคำนวณ (ใช้ฟังก์ชันของเพื่อน)
    // รอบที่ 1: คูณ หาร เปอร์เซ็นต์ ก่อน
    process(nums, ops, &count, "*/%");
    
    // รอบที่ 2: บวก ลบ 
    process(nums, ops, &count, "+-");

    // 4. แสดงผลลัพธ์
    printf("Result: %.2f\n", nums[0]);

    return 0;
}
