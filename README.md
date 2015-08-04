# cpwd
## Command-line password manager for your various accounts, written in C.

cpwd is a C port of [npwd] (https://github.com/kaepora/npwd) by [Nadim Kobeissi] (https://nadim.computer) - simple, stateless password manager. You enter a master key and the name of an account (ex. "Twitter"), wait a few seconds, and cpwd generates a password for that account (now it just prints it, in future it will ready in your clipboard). You can reuse the same master key for all your accounts, and cpwd will generate a different password for every account. Every time you want to log in, just launch cpwd and enter the same master key and account name. Simple! Useful!

### Benefits
1. Memorize a single master key, but still get a different password for every account.
2. Quick and easy command-line access.
3. NOT READY YET: Copies password straight to clipboard then clears clipboard automatically in 15 seconds.
4. Doesn't store anything: no password databases to manage.

### Installation

`git clone https://github.com/postboy/cpwd.git

chmod +x build.sh && ./build.sh`

Add `alias cpwd='/path/to/./cpwd'` in your `.bashrc` file for adding a command "cpwd" to your shell.

### Usage
1. `cpwd`
2. Enter your master key (hidden) (same for all accounts).
3. Enter the name of your account (ex. "Twitter", "GitHub").
4. NOT READY YET: In a few seconds, your password for that account is in your clipboard. Clipboard is cleared automatically after 15 seconds for security.

### Notes
1. cpwd is fully compatibile with latest npwd 1.0.6 and offers the same functional (for now, except working with clipboard). The only real difference is that cpwd is written on C and hasn't any external dependencies while npwd is written in JavaScript and requies installation of [Node.JS] (https://nodejs.org) & [npm] (https://www.npmjs.com).
2. Key derivation is done with [scrypt] (https://www.tarsnap.com/scrypt.html). N = 2<sup>17</sup> = 131072, r = 8, p = 1, L = 16. Account name acts as salt.
3. Account names are lowercased automatically for usability. "GitHub" == "github".

### Licenses
cpwd itself is licensed under [GPL v3] (https://www.gnu.org/licenses/gpl-3.0.en.html) as a port of GPL v3-licensed npwd. cpwd uses parts of [scrypt] (https://www.tarsnap.com/scrypt.html) 1.1.6 licensed under [BSD 2-Clause] (http://opensource.org/licenses/bsd-license.php) and parts of [xclip] (http://xclip.sourceforge.net) 0.12 licensed under [GPL v2] (https://www.gnu.org/licenses/old-licenses/gpl-2.0.html).

## Contributors
Developer: Zuboff Ivan // anotherdiskmag on gooooooogle mail
