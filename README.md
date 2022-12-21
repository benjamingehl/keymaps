# My keymap

The repo contains my custom keymap for the GMMK Pro featuring:

- [A two layer keymap](https://github.com/benjamingehl/keymaps/blob/a18a213d4130de9660ab313de588f077688a10cb/benjamingehl/keymap.c#L30-L56) (base + function layer)
- [RGB highlight for the assigned Fn keys](https://github.com/benjamingehl/keymaps/blob/a18a213d4130de9660ab313de588f077688a10cb/benjamingehl/keymap.c#L148-L171)
- [Secondary redo/undo function for the rotary encoder](https://github.com/benjamingehl/keymaps/blob/a18a213d4130de9660ab313de588f077688a10cb/benjamingehl/keymap.c#L61-L106) (`Fn+rotation`)
- [OS toggle](https://github.com/benjamingehl/keymaps/blob/a18a213d4130de9660ab313de588f077688a10cb/benjamingehl/keymap.c#L110-L114) (`Fn+o`)
- [Caps lock toggle indicator](https://github.com/benjamingehl/keymaps/blob/a18a213d4130de9660ab313de588f077688a10cb/benjamingehl/keymap.c#L141-L146)

# Setup
1) Create `env.h` from `env.h.example`
2) Optional: Setup the Autocorrection library in `autocorrection_dict.txt`

# Building the keymap

1) Run `docker compose up`
2) Check logs for any errors
3) On successful compilation the built binary for flashing the keyboard should be under the `build` folder


*Based on the default [GMMK Pro ANSI keymap](https://github.com/qmk/qmk_firmware/blob/master/keyboards/gmmk/pro/ansi/keymaps/default/keymap.c)*