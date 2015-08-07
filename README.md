## cpwd 1.2 - tiny and handy password manager.

cpwd is simple, stateless password manager. You enter a master key and the name of an account (ex. "Twitter"), wait a few seconds, and cpwd generates a password for that account ready in your clipboard. You can reuse the same master key for all your accounts, and cpwd will generate a different password for every account. Every time you want to log in, just launch cpwd and enter the same master key and account name. Simple! Useful!

cpwd is a C port of [npwd] (https://github.com/kaepora/npwd) by [Nadim Kobeissi] (https://nadim.computer).

### Benefits
1. Memorize a single master key, but still get a different password for every account.
2. Quick and easy command-line access.
3. Copies password straight to clipboard then clears clipboard automatically in 15 seconds.
4. Doesn't store anything: no password databases to manage.

### Usage
1. a) Run `cpwd account_name`, ex. `cpwd twitter`, or
b) Run `cpwd`, then enter the name of your account (ex. "twitter").

2. Enter your master key (hidden, same for all accounts).
3. In a few seconds, your password for that account is in your clipboard. Clipboard is cleared automatically after 15 seconds for security.

### Notes
1. **Weak master key ruins everything**. Your master key should have at least 8 characters, contain lowercase and uppercase letters, numbers and special symbols.
2. cpwd is fully compatibile with latest npwd 1.0.6 and offers the same functional plus account name definition in command. cpwd allows you to get maximum speed of work while npwd is much easier to install. cpwd is written in C while npwd is written in JavaScript, thus depends on `Node.JS` and `npm`.
3. Key derivation is done with [scrypt] (https://www.tarsnap.com/scrypt.html). Parameters: N = 2<sup>17</sup> = 131072, r = 8, p = 1, L = 16. Account name acts as salt.
4. Account names are lowercased automatically for usability. "GitHub" == "github".

### Platforms
Tested: Linux.

Not tested, but probably supported: OpenBSD, Windows, Mac OS X.

### Installation
1. `git clone https://github.com/postboy/cpwd.git` to download repository.
2. Comment all code in platform-specific section that is unuseful for your system (that's easy).
3. Build cpwd. On *nix systems with GCC you can do it via `./build.sh`.
4. *nix only: add `alias cpwd='/path/to/./cpwd'` in your `.bashrc` file for adding a command "cpwd" to your shell. If you call it just "p" instead of "cpwd", you can launch it even faster!
5. Linux/OpenBSD only: install `xclip` or `xsel` package for working with clipboard.

### Does cpwd works too slow?
If you don't satisfied with cpwd speed, you can make it many times faster!

1. Check if your processor supports SSE (on *nix you just run `grep sse /proc/cpuinfo` to do it). If it does, compile against crypto_scrypt-sse.c instead of crypto_scrypt-ref.c (on GCC add a flag `-march=native` for successful compilation).
2. Enable optimization in your compiler. If you use GCC, you can do it with flags `-march=native` (compile just for that processor) plus `-O1` or `-O2` or `-O3` (test them all and use the best for you).

### See also
1. [npwd] (https://github.com/kaepora/npwd) — imagine cpwd with very easy installation, but maybe not that fast work :)
2. [PwdHash] (https://www.pwdhash.com) has a similar idea but uses hashing instead of key derivation function, thus less secure.
3. [Password manager without a password manager] (https://gist.github.com/jaseg/3334991) had a somewhat similar idea, used hashing instead of key derivation function and was broken.

### License
cpwd itself is licensed under [GPL v3] (https://www.gnu.org/licenses/gpl-3.0.en.html). cpwd uses parts of [scrypt] (https://www.tarsnap.com/scrypt.html) 1.1.6 licensed under [BSD 2-Clause] (http://opensource.org/licenses/bsd-license.php) and [GCC Poison] (http://blog.leafsr.com/2013/12/02/gcc-poison) which is public domain.

### Author
Zuboff Ivan // anotherdiskmag on gooooooogle mail
