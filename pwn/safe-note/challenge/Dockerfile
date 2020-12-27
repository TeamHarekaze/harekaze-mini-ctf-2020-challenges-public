FROM ubuntu:20.10

RUN apt-get update && apt-get install -y xinetd \
    && useradd -m safenote \
    && chown -R root:root /home/safenote

ADD safenote /home/safenote/
ADD flag /home/safenote/
ADD xinetd.conf /etc/xinetd.d/safenote

RUN chmod 644 /home/safenote/flag \
    && chmod 755 /home/safenote/safenote \
    && chmod 644 /etc/xinetd.d/safenote

EXPOSE 30004

CMD ["/usr/sbin/xinetd", "-dontfork"]

