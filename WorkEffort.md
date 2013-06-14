Work Effort
=====

Currently, the source will build as is, but refuses to load properly into the wineloader.

We currently suspect a build issue; Thanks to the work of André Hentschel (visit #winehackers on IRC) to join in the discussion, we are cleaning up the automated build system to attempt to more closely replicate the build conditions found on Windows.

I have also begun converting the source to ISO C++, in the hopes that this will uncover a hidden pointer error/problem somewhere in the source.

Problems
===
- Pointer issues and integer problems are rampant
- Many different standards of integer/uint are lying around
- Should consolidated to a couple of relevent types

PLEASE NOTE:

The source in the repository is significantly altered to avoid circular dependency issues which were encountered during my initial builds.

This includes extensive splitting of source-from-header into .cpp files, and as such the .vcproj is not currently in a usable state to regenerate the Makefile using winemaker.

As such, the current work is being focused into bringing the notepadPlus.vcproj back into line with the state of the source, so that more automated rebuilds can be attempted.
