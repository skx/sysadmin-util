#
# This makes the sysadmin-utils more easily used with antigen,
# oh-my-zsh, and any other framework that understands their
# plugin structure.
#
# Add our plugin's root diretory to user's path
PLUGIN_D="$(dirname $0)"
export PATH=${PATH}:${PLUGIN_D}
