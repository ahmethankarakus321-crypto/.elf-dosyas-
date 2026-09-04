#include <tamtypes.h>
#include <kernel.h>
#include <sifrpc.h>
#include <loadfile.h>
#include <debug.h>
#include <libpad.h>
#include <audsrv.h>

extern unsigned char ses_wav[];
extern unsigned int ses_wav_size;

static char padBuf[256] __attribute__((aligned(64)));

void win_media_player_ciz() {
    scr_printf("\n");
    scr_printf("   =====================================================\n");
    scr_printf("   |  [>] WINDOWS MEDIA PLAYER v1.0 (PS2 EDITION)       |\n");
    scr_printf("   =====================================================\n");
    scr_printf("   |                                                   |\n");
    scr_printf("   |  Calan Parca: Congo Democratic - Remix.wav        |\n");
    scr_printf("   |  Durum      : [ BASS PATLIYOR... ]                 |\n");
    scr_printf("   |  Ses Duzeyi : [||||||||||||||||||||] %%100        |\n");
    scr_printf("   =====================================================\n");
    scr_printf("   KNK SEN SES BOLUMUNDESINNN !\n\n");
}

int main() {
    int pad_ok = 0;
    u32 paddata;
    int old_state_triangle = 0;

    init_scr();
    
    SifInitRpc(0);
    SifLoadModule("rom0:SIO2MAN", 0, NULL);
    SifLoadModule("rom0:PADMAN", 0, NULL);
    SifLoadModule("rom0:LIBSD", 0, NULL);

    padInit(0);

    if (audsrv_init() == 0) {
        struct audsrv_fmt_t format;
        format.bits = 16;
        format.freq = 44100;
        format.channels = 2;
        audsrv_set_format(&format);
        audsrv_set_volume(MAX_VOLUME);
    }

    if (padPortOpen(0, 0, padBuf) > 0) {
        pad_ok = 1;
    }

    scr_printf("\n\n");
    scr_printf("     PS2 AHMET-OS MEDIA PLAYER HAZIR!\n");
    scr_printf("     [ UCGEN ] - Congo Remix Cal!\n\n");

    while (1) {
        if (pad_ok) {
            struct padButtonStatus buttons;
            int ret = padRead(0, 0, &buttons);

            if (ret > 0) {
                paddata = 0xffff ^ buttons.btns;

                if (paddata & PAD_TRIANGLE) {
                    if (!old_state_triangle) {
                        win_media_player_ciz();
                        audsrv_play_audio((char*)ses_wav, ses_wav_size);
                        old_state_triangle = 1;
                    }
                } else {
                    old_state_triangle = 0;
                }
            }
        }
        
        int i;
        for (i = 0; i < 100000; i++) {
            asm("nop");
        }
    }

    audsrv_quit();
    padPortClose(0, 0);
    return 0;
}
