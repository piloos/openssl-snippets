OPENSSLSNIPPETS_LICENSE = Barco
OPENSSLSNIPPETS_VERSION = HEAD
OPENSSLSNIPPETS_SITE = /home/lodco/misc/openssl-snippets/
OPENSSLSNIPPETS_SITE_METHOD = local
OPENSSLSNIPPETS_INSTALL_STAGING = YES
OPENSSLSNIPPETS_INSTALL_TARGET = YES

define OPENSSLSNIPPETS_BUILD_CMDS 
  $(MAKE) CC="$(TARGET_CC)" LD="$(TARGET_LD)" -C $(@D) generate_priv_key
  $(MAKE) CC="$(TARGET_CC)" LD="$(TARGET_LD)" -C $(@D) read_random
endef

define OPENSSLSNIPPETS_INSTALL_TARGET_CMDS
  cp $(@D)/generate_priv_key.o $(@D)/read_random.o $(@D)/generate_x_times_priv_key.sh $(TARGET_DIR)/bin/
endef

define OPENSSLSNIPPETS_UNINSTALL_TARGET_CMDS
  rm $(TARGET_DIR)/generate_priv_key.o $(TARGET_DIR)/read_random.o $(TARGET_DIR)/generate_x_times_priv_key.sh
endef

$(eval $(generic-package))
