#include "Player.h"
#include "GameAPI/Game.h"
#include "Zone.h"

ObjectZone *Zone;

ObjectPlayer *Player;

void Player_Gravity_False(void)
{
    RSDK_THIS(Player);

    if (self->camera)
        self->camera->disableYOffset = false;

    self->jumpAbilityState = 0;
}

void Player_State_KnuxGlideDrop_Hook(void)
{
    RSDK_THIS(Player);

    if (self->onGround) {

        if (!self->timer)
            RSDK.PlaySfx(Player->sfxLand, false, 255);

        Player_Gravity_False();

        if (abs(Zone->autoScrollSpeed) > 0x20000) {
            if (Zone->autoScrollSpeed <= 0) {
                self->groundVel  = Zone->autoScrollSpeed + 0x20000;
                self->velocity.x = Zone->autoScrollSpeed + 0x20000;
            }
            else {
                self->groundVel  = Zone->autoScrollSpeed - 0x20000;
                self->velocity.x = Zone->autoScrollSpeed - 0x20000;
            }
            self->timer = 16;
        }
        else {
            self->groundVel  = 0;
            self->velocity.x = 0;
            RSDK.SetSpriteAnimation(self->aniFrames, ANI_GLIDE_LAND, &self->animator, false, 0);
            if (self->jumpPress & self->down) {
                Player_Action_Spindash();
                self->skidding = 0;
                self->timer    = 0;
            }
            if (self->jumpPress & !self->down) {
                Player_Action_Jump(self);
                self->skidding = 0;
                self->timer    = 0;
            }
        }
        if (self->timer >= 16) {
            self->state    = Player_State_Ground;
            self->skidding = 0;
            self->timer    = 0;
        }
        else {
            self->timer++;
        }
    }
}
