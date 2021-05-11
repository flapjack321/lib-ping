/*-
 * SPDX-License-Identifier: BSD-2-Clause-FreeBSD
 *
 * Copyright (C) 2019 Jan Sucan <jansucan@FreeBSD.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <sys/cdefs.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "usage.h"
#ifdef INET
#include "ping.h"
#endif
#ifdef INET6
#include "ping6.h"
#endif

#if defined(INET) && defined(INET6)
#define	OPTSTR ":46"
#elif defined(INET)
#define OPTSTR ":4"
#elif defined(INET6)
#define	OPTSTR ":6"
#else
#define OPTSTR ""
#endif

void
usage(void)
{
	(void)fprintf(stderr,
	    "usage:\n"
#ifdef INET
	    "\tping [-4AaDdfHnoQqRrv] [-C pcp] [-c count] "
	    "[-G sweepmaxsize]\n"
	    "	    [-g sweepminsize] [-h sweepincrsize] [-i wait] "
	    "[-l preload]\n"
	    "	    [-M mask | time] [-m ttl]"
#ifdef IPSEC
	    "[-P policy] "
#endif
	    "[-p pattern] [-S src_addr] \n"
	    "	    [-s packetsize] [-t timeout] [-W waittime] [-z tos] "
	    "IPv4-host\n"
	    "\tping [-4AaDdfHLnoQqRrv] [-C pcp] [-c count] [-I iface] "
	    "[-i wait]\n"
	    "	    [-l preload] [-M mask | time] [-m ttl] "
#ifdef IPSEC
	    "[-P policy] "
#endif
	    "[-p pattern]\n"
	    "	    [-S src_addr] [-s packetsize] [-T ttl] [-t timeout] [-W waittime]\n"
	    "            [-z tos] IPv4-mcast-group\n"
#endif /* INET */
#ifdef INET6
            "\tping [-6aADd"
#if defined(IPSEC) && !defined(IPSEC_POLICY_IPSEC)
            "E"
#endif
            "fHnNoOq"
#ifdef IPV6_USE_MIN_MTU
            "u"
#endif
            "vyY"
#if defined(IPSEC) && !defined(IPSEC_POLICY_IPSEC)
            "Z"
#endif
	    "] "
            "[-b bufsiz] [-c count] [-e gateway]\n"
            "            [-I interface] [-i wait] [-k addrtype] [-l preload] "
            "[-m hoplimit]\n"
            "            [-p pattern]"
#if defined(IPSEC) && defined(IPSEC_POLICY_IPSEC)
            " [-P policy]"
#endif
            " [-S sourceaddr] [-s packetsize] [-t timeout]\n"
	    "	    [-W waittime] [-z tclass] [IPv6-hops ...] IPv6-host\n"
#endif	/* INET6 */
	    );

	exit(1);
}
