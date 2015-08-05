# cpwd 1.1
## Command-line password manager for your various accounts, written in C.

cpwd is a C port of [npwd] (https://github.com/kaepora/npwd) by [Nadim Kobeissi] (https://nadim.computer) - simple, stateless password manager. You enter a master key and the name of an account (ex. "Twitter"), wait a few seconds, and cpwd generates a password for that account ready in your clipboard. You can reuse the same master key for all your accounts, and cpwd will generate a different password for every account. Every time you want to log in, just launch cpwd and enter the same master key and account name. Simple! Useful!

### Benefits
1. Memorize a single master key, but still get a different password for every account.
2. Quick and easy command-line access.
3. Copies password straight to clipboard then clears clipboard automatically in 15 seconds.
4. Doesn't store anything: no password databases to manage.

### Platforms
Tested: Linux.

Not tested, but probably supported: OpenBSD, Windows, Mac OS X.

### Installation
1. `git clone https://github.com/postboy/cpwd.git` to download repository.
2. Comment all code in platform-specific section that is unuseful for your system (that's easy).
3. Build cpwd. On *nix systems with gcc you can do it via `chmod +x build.sh && ./build.sh`.
4. *nix only: add `alias cpwd='/path/to/./cpwd'` in your `.bashrc` file for adding a command "cpwd" to your shell.
5. Linux/OpenBSD only: install `xclip` or `xsel` package for working with clipboard.

### Usage
1. `cpwd`
2. Enter the name of your account (ex. "Twitter", "GitHub").
3. Enter your master key (hidden, same for all accounts).
4. In a few seconds, your password for that account is in your clipboard. Clipboard is cleared automatically after 15 seconds for security.

### Notes
1. cpwd is fully compatibile with latest npwd 1.0.6 and offers the same functional. The only real differences are that cpwd is written on C while npwd is written in JavaScript, thus depends on `Node.JS` and `npm`.
2. Key derivation is done with [scrypt] (https://www.tarsnap.com/scrypt.html). N = 2<sup>17</sup> = 131072, r = 8, p = 1, L = 16. Account name acts as salt.
3. Account names are lowercased automatically for usability. "GitHub" == "github".

### Legal
cpwd itself is licensed under [GPL v3] (https://www.gnu.org/licenses/gpl-3.0.en.html) as a port of GPL v3-licensed npwd.

cpwd uses parts of [scrypt] (https://www.tarsnap.com/scrypt.html) 1.1.6 licensed under [BSD 2-Clause] (http://opensource.org/licenses/bsd-license.php). 

Commands for working with clipboard are taken from [node-copy-paste] (https://github.com/xavi-/node-copy-paste) 1.1.3.

### Contributors
Developer: Zuboff Ivan // anotherdiskmag on gooooooogle mail
