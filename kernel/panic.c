// kernel/panic.c
#include "panic.h"
#include "console.h"   // seu driver de saída (print na tela)
#include <stdarg.h>    // para formatar mensagens

// Função principal de panic
void kernel_panic(const char *msg, int cpu, const char *file) {
    console_set_color(0x4F); // fundo vermelho, texto branco (opcional)
    kprintf("\n\n=== KERNEL PANIC ===\n");
    kprintf("FATAL ERROR!\n");
    kprintf("not syncing: %s\n", msg);
    kprintf("error in CPU#%d\n", cpu);
    kprintf("error in file: %s\n", file);
    kprintf("system halted.\n");
    
    // trava o sistema
    for (;;) { __asm__("hlt"); }
}
