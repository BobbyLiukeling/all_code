#!/bin/bash -ex
#
# DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS HEADER.
#
# Copyright (c) 2017 Oracle and/or its affiliates. All rights reserved.
#
# The contents of this file are subject to the terms of either the GNU
# General Public License Version 2 only ("GPL") or the Common Development
# and Distribution License("CDDL") (collectively, the "License").  You
# may not use this file except in compliance with the License.  You can
# obtain a copy of the License at
# https://oss.oracle.com/licenses/CDDL+GPL-1.1
# or LICENSE.txt.  See the License for the specific
# language governing permissions and limitations under the License.
#
# When distributing the software, include this License Header Notice in each
# file and include the License file at LICENSE.txt.
#
# GPL Classpath Exception:
# Oracle designates this particular file as subject to the "Classpath"
# exception as provided by Oracle in the GPL Version 2 section of the License
# file that accompanied this code.
#
# Modifications:
# If applicable, add the following below the License Header, with the fields
# enclosed by brackets [] replaced by your own identifying information:
# "Portions Copyright [year] [name of copyright owner]"
#
# Contributor(s):
# If you wish your version of this file to be governed by only the CDDL or
# only the GPL Version 2, indicate your decision by adding "[Contributor]
# elects to include this software in this distribution under the [CDDL or GPL
# Version 2] license."  If you don't indicate a single choice of license, a
# recipient has the option to distribute your version of this file under
# either the CDDL, the GPL Version 2 or to extend the choice of license to
# its licensees as provided above.  However, if you add GPL Version 2 code
# and therefore, elected the GPL Version 2 license, then the option applies
# only if the new code is made subject to such option by the copyright
# holder.
#

test_run(){
	ADMIN_PORT=45707
	JMS_PORT=45708
	JMX_PORT=45709
	ORB_PORT=45710
	SSL_PORT=45711
	INSTANCE_PORT=45712
	INSTANCE_HTTPS_PORT=45718
	INSTANCE_PORT_2=45719
	INSTANCE_PORT_3=45720
	ALTERNATE_PORT=45713
	ORB_SSL_PORT=45714
	ORB_SSL_MUTUALAUTH_PORT=45715
	DB_PORT=45716
	DB_PORT_2=45717

	export ADMIN_PORT JMS_PORT JMX_PORT ORB_PORT SSL_PORT INSTANCE_PORT INSTANCE_HTTPS_PORT INSTANCE_PORT_2 INSTANCE_PORT INSTANCE_PORT_3 ALTERNATE_PORT ORB_SSL_PORT ORB_SSL_MUTUALAUTH_PORT DB_PORT DB_PORT_2

	rm -rf $S1AS_HOME/domains/domain1
	cd $APS_HOME

	echo "AS_ADMIN_PASSWORD=" > temppwd
	cat $APS_HOME/temppwd
	$S1AS_HOME/bin/asadmin --user anonymous --passwordfile $APS_HOME/temppwd create-domain --adminport ${ADMIN_PORT} --domainproperties jms.port=${JMS_PORT}:domain.jmxPort=${JMX_PORT}:orb.listener.port=${ORB_PORT}:http.ssl.port=${SSL_PORT}:orb.ssl.port=${ORB_SSL_PORT}:orb.mutualauth.port=${ORB_SSL_MUTUALAUTH_PORT} --instanceport ${INSTANCE_PORT} domain1

	#Create 
	echo "admin.domain=domain1
	admin.domain.dir=\${env.S1AS_HOME}/domains
	admin.port=${ADMIN_PORT}
	admin.user=anonymous
	admin.host=localhost
	http.port=${INSTANCE_PORT}
	https.port=${SSL_PORT}
	http.host=localhost
	http.address=127.0.0.1
	http.alternate.port=${ALTERNATE_PORT}
	orb.port=${ORB_PORT}
	admin.password=
	ssl.password=changeit
	master.password=changeit
	admin.password.file=\${env.APS_HOME}/config/adminpassword.txt
	appserver.instance.name=server
	config.dottedname.prefix=server
	resources.dottedname.prefix=domain.resources
	results.mailhost=localhost
	results.mailer=QLTestsForPEInstallOrDASInEEInstall@sun.com
	results.mailee=yourname@sun.com
	autodeploy.dir=\${env.S1AS_HOME}/domains/\${admin.domain}/autodeploy
	precompilejsp=true
	jvm.maxpermsize=192m
	appserver.instance.dir=\${admin.domain.dir}/\${admin.domain}" > config.properties

	(jps |grep Main |cut -f1 -d" " | xargs kill -9  > /dev/null 2>&1) || true

	cd $S1AS_HOME/domains/domain1/config/
	sed "s/1527/${DB_PORT}/g" domain.xml > domain.xml.replaced
	mv domain.xml.replaced domain.xml
	grep PortNumber domain.xml

	cd $APS_HOME/config
	(rm derby.properties.replaced  > /dev/null 2>&1) || true
	sed "s/1527/${DB_PORT}/g" derby.properties > derby.properties.replaced
	rm derby.properties
	sed "s/1528/${DB_PORT_2}/g" derby.properties.replaced > derby.properties
	cat derby.properties

	cd $APS_HOME/devtests/transaction/ee

	ant -Dsave.logs=true $TARGET | tee $TEST_RUN_LOG


	ant dev-report
}

list_test_ids(){
    echo transaction_ee_all transaction-ee-1 transaction-ee-2 transaction-ee-3 transaction-ee-4
}

get_test_target(){
	case $1 in
		transaction_ee_all )
			TARGET=all
			export TARGET;;
                * )
                        TARGET=$1
                        export TARGET;;
	esac

}

run_test_id(){
	source `dirname $0`/../../../../common_test.sh
	kill_process
	delete_gf
	download_test_resources glassfish.zip version-info.txt
	unzip_test_resources $WORKSPACE/bundles/glassfish.zip
	cd `dirname $0`
	test_init
	get_test_target $1
	test_run
	check_successful_run
    generate_junit_report $1
    change_junit_report_class_names
}

post_test_run(){
    copy_test_artifects
    upload_test_results
    delete_bundle
    cd -
}

OPT=$1
TEST_ID=$2

case $OPT in
	list_test_ids )
		list_test_ids;;
	run_test_id )
		trap post_test_run EXIT
		run_test_id $TEST_ID ;;
esac
 




