
# Create New Docker Images

## Start

See https://github.com/gentoo/gentoo-docker-images for reference.

    docker create -v /usr/portage --name myportagesnapshot gentoo/portage:latest /bin/true
    docker run -ti --volumes-from myportagesnapshot --name mygentoo --hostname mygentoo gentoo/stage3-amd64:latest /bin/bash

## Run Container

    docker start -ai mygentoo


# Backup

## Save copies

First commit containers to images:

    docker ps -a
    docker commit ff8b82bd792c myportagesnapshot-2018-08-31
    docker commit c70f7dc12074 gentoo-2018-08-30

Then, save images to tar files:

    docker save -o /tmp/myportagesnapshot-2018-08-31.tar myportagesnapshot-2018-08-31
    docker save -o /tmp/gentoo-2018-08-30.tar gentoo-2018-08-30

## Restore

    docker load -i myportagesnapshot-2018-08-31.tar
    docker load -i gentoo-2018-08-30.tar
    # same as the cmds in create section but different image names.
    docker create -v /usr/portage --name myportagesnapshot myportagesnapshot-2018-08-31 /bin/true
    docker run -ti --volumes-from myportagesnapshot --name mygentoo --hostname mygentoo gentoo/stage3-amd64:latest /bin/bash
