# This is an automatically generated record.
# The area between QNX Internal Start and QNX Internal End is controlled by
# the QNX IDE properties.


ifndef QCONFIG
QCONFIG=qconfig.mk
endif
include $(QCONFIG)

#===== USEFILE - the file containing the usage message for the application. 
USEFILE=

# Next lines are for C++ projects only
EXTRA_SUFFIXES+=cxx cpp
#===== LDFLAGS - add the flags to the linker command line.
LDFLAGS+=-lang-c++
VFLAG_g=-gstabs+


#===== EXTRA_SILENT_VARIANTS - variants that are not appended to the result binary name (like MyBin_g)
EXTRA_SILENT_VARIANTS+=gcc335
#===== CCFLAGS - add the flags to the C compiler command line. 
CCFLAGS_gcc335+=-g
include $(MKFILES_ROOT)/qmacros.mk
#QNX internal start
ifeq ($(filter g, $(VARIANT_LIST)),g)
DEBUG_SUFFIX=_g
LIB_SUFFIX=_g
else
DEBUG_SUFFIX=$(filter-out $(VARIANT_BUILD_TYPE) le be,$(VARIANT_LIST))
ifeq ($(DEBUG_SUFFIX),)
DEBUG_SUFFIX=_r
else
DEBUG_SUFFIX:=_$(DEBUG_SUFFIX)
endif
endif

EXPRESSION = $(firstword $(foreach a, $(1)_$(CPUDIR)$(DEBUG_SUFFIX)  $(1)$(DEBUG_SUFFIX) \
			$(1)_$(CPUDIR) $(1), $(if $($(a)),$(a),)))
MERGE_EXPRESSION= $(foreach a, $(1)_$(CPUDIR)$(2)$(DEBUG_SUFFIX) $(1)$(2)$(DEBUG_SUFFIX) \
		$(1)_$(CPUDIR)$(2) $(1)$(2) , $($(a)))

GCC_VERSION:=$($(firstword $(foreach a, GCC_VERSION_$(CPUDIR) GCC_VERSION, \
			$(if $($(a)), $(a), ))))

EXTRA_LIBVPATH := $(call MERGE_EXPRESSION, EXTRA_LIBVPATH)
extra_incvpath_tmp:=$(call MERGE_EXPRESSION,EXTRA_INCVPATH,)
EXTRA_INCVPATH = $(call MERGE_EXPRESSION,EXTRA_INCVPATH,_@$(basename $@)) \
	$(extra_incvpath_tmp)
EXTRA_SRCVPATH := $(call MERGE_EXPRESSION, EXTRA_SRCVPATH)
EXTRA_OBJS := $($(call EXPRESSION,EXTRA_OBJS))

CCFLAGS_D = $(CCFLAGS$(DEBUG_SUFFIX)) $(CCFLAGS_$(CPUDIR)$(DEBUG_SUFFIX)) \
			$(CCFLAGS_@$(basename $@)$(DEBUG_SUFFIX)) 					  \
			$(CCFLAGS_$(CPUDIR)_@$(basename $@)$(DEBUG_SUFFIX))
LDFLAGS_D = $(LDFLAGS$(DEBUG_SUFFIX)) $(LDFLAGS_$(CPUDIR)$(DEBUG_SUFFIX))

CCFLAGS += $(CCFLAGS_$(CPUDIR))  $(CCFLAGS_@$(basename $@)) 				  \
		   $(CCFLAGS_$(CPUDIR)_@$(basename $@))  $(CCFLAGS_D)
LDFLAGS += $(LDFLAGS_$(CPUDIR)) $(LDFLAGS_D)

LIBS:=$(patsubst %S_g, %_gS, $(foreach token, $($(call EXPRESSION,LIBS)),$(if $(findstring ^, $(token)), $(subst ^,,$(token))$(LIB_SUFFIX), $(token))))
libnames:= $(subst lib-Bdynamic.a, ,$(subst lib-Bstatic.a, , $(libnames)))
libopts := $(subst -l-B,-B, $(libopts))

BUILDNAME:=$($(call EXPRESSION,BUILDNAME))$(if $(suffix $(BUILDNAME)),,$(IMAGE_SUFF_$(BUILD_TYPE)))
BUILDNAME_SAR:= $(patsubst %$(IMAGE_SUFF_$(BUILD_TYPE)),%S.a,$(BUILDNAME))

POST_BUILD:=$($(call EXPRESSION,POST_BUILD))
#QNX internal end
include $(MKFILES_ROOT)/qtargets.mk
OPTIMIZE_TYPE=$(OPTIMIZE_TYPE_$(filter g, $(VARIANTS)))
OPTIMIZE_TYPE_g=none
