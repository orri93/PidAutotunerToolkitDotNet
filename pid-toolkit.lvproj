<?xml version='1.0' encoding='UTF-8'?>
<Project Type="Project" LVVersion="18008000">
	<Property Name="varPersistentID:{00940816-5564-46E6-B1C4-1F463CA01F08}" Type="Ref">/My Computer/pid-toolkit-modbus.lvlib/F300002</Property>
	<Property Name="varPersistentID:{0C933F7A-54FD-4AC1-B82D-1BCC20800239}" Type="Ref">/My Computer/pid-toolkit-modbus.lvlib/300010</Property>
	<Property Name="varPersistentID:{119E589F-1825-438E-8867-AA6B980751DF}" Type="Ref">/My Computer/pid-toolkit-modbus.lvlib/F400003</Property>
	<Property Name="varPersistentID:{149D18AB-9CFC-412A-A968-03EF8C778AB5}" Type="Ref">/My Computer/pid-toolkit-modbus.lvlib/F300008</Property>
	<Property Name="varPersistentID:{19400AB9-561B-4A42-A754-D95EAD04F80F}" Type="Ref">/My Computer/pid-toolkit-modbus.lvlib/400016</Property>
	<Property Name="varPersistentID:{21F9DCCB-3150-4C6A-A74B-2967D9201E66}" Type="Ref">/My Computer/pid-toolkit-modbus.lvlib/F400011</Property>
	<Property Name="varPersistentID:{4DF2F251-1BA4-42DB-A21A-221F6D578D92}" Type="Ref">/My Computer/pid-toolkit-modbus.lvlib/F400013</Property>
	<Property Name="varPersistentID:{51CF2893-F4FC-48A9-9986-AD631C5B77C5}" Type="Ref">/My Computer/pid-toolkit-modbus.lvlib/OffHook</Property>
	<Property Name="varPersistentID:{55205E8C-8905-4A84-8273-B83F14CC4D19}" Type="Ref">/My Computer/pid-toolkit-modbus.lvlib/Updating</Property>
	<Property Name="varPersistentID:{57CD2342-077E-43C6-8C3E-82E545984A3E}" Type="Ref">/My Computer/pid-toolkit-modbus.lvlib/UpdateNow</Property>
	<Property Name="varPersistentID:{63908863-1481-4ABA-9D13-4A0735D1C82D}" Type="Ref">/My Computer/pid-toolkit-modbus.lvlib/400002</Property>
	<Property Name="varPersistentID:{72E61CCE-9F86-4DB5-9909-41D21A817B3D}" Type="Ref">/My Computer/pid-toolkit-modbus.lvlib/UpdateRate</Property>
	<Property Name="varPersistentID:{73294D6B-F762-43A2-8A4E-018A0C47ACD9}" Type="Ref">/My Computer/pid-toolkit-modbus.lvlib/F300006</Property>
	<Property Name="varPersistentID:{87D076C9-225C-4E29-87CA-3F69F0361E7E}" Type="Ref">/My Computer/pid-toolkit-modbus.lvlib/F400009</Property>
	<Property Name="varPersistentID:{96A78492-FEA3-4B66-B02B-5E4F69BAA527}" Type="Ref">/My Computer/pid-toolkit-modbus.lvlib/F400005</Property>
	<Property Name="varPersistentID:{AFD79F35-AF6B-41CB-8CC4-D28AD26DB63A}" Type="Ref">/My Computer/pid-toolkit-modbus.lvlib/F300004</Property>
	<Property Name="varPersistentID:{BD3C58E4-5DF7-43D9-83AE-2CCC289DA98E}" Type="Ref">/My Computer/pid-toolkit-modbus.lvlib/CommFail</Property>
	<Property Name="varPersistentID:{C40FFDE4-7DD2-478F-B1A5-B7F330F75D6A}" Type="Ref">/My Computer/pid-toolkit-modbus.lvlib/300001</Property>
	<Property Name="varPersistentID:{CBA2277C-64EC-4BF2-84E4-EAAF37C25C1C}" Type="Ref">/My Computer/pid-toolkit-modbus.lvlib/400001</Property>
	<Property Name="varPersistentID:{ED459AA3-A22C-4E92-8C79-233CA4AE21B5}" Type="Ref">/My Computer/pid-toolkit-modbus.lvlib/400015</Property>
	<Property Name="varPersistentID:{F02AA7C8-5903-4BC4-915D-B3DCFAFCF19A}" Type="Ref">/My Computer/pid-toolkit-modbus.lvlib/F400007</Property>
	<Item Name="My Computer" Type="My Computer">
		<Property Name="server.app.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.control.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.tcp.enabled" Type="Bool">false</Property>
		<Property Name="server.tcp.port" Type="Int">0</Property>
		<Property Name="server.tcp.serviceName" Type="Str">My Computer/VI Server</Property>
		<Property Name="server.tcp.serviceName.default" Type="Str">My Computer/VI Server</Property>
		<Property Name="server.vi.callsEnabled" Type="Bool">true</Property>
		<Property Name="server.vi.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="specify.custom.address" Type="Bool">false</Property>
		<Item Name="pid-toolkit-modbus.lvlib" Type="Library" URL="../labview/pid-toolkit-modbus.lvlib"/>
		<Item Name="pid-toolkit.lvlib" Type="Library" URL="../labview/pid-toolkit.lvlib"/>
		<Item Name="Dependencies" Type="Dependencies">
			<Item Name="vi.lib" Type="Folder">
				<Item Name="BuildHelpPath.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/BuildHelpPath.vi"/>
				<Item Name="Check Special Tags.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Check Special Tags.vi"/>
				<Item Name="Clear Errors.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Clear Errors.vi"/>
				<Item Name="Close Panel.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/victl.llb/Close Panel.vi"/>
				<Item Name="Convert property node font to graphics font.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Convert property node font to graphics font.vi"/>
				<Item Name="Details Display Dialog.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Details Display Dialog.vi"/>
				<Item Name="Dflt Data Dir.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/file.llb/Dflt Data Dir.vi"/>
				<Item Name="DialogType.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/DialogType.ctl"/>
				<Item Name="DialogTypeEnum.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/DialogTypeEnum.ctl"/>
				<Item Name="Error Code Database.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Error Code Database.vi"/>
				<Item Name="ErrWarn.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/ErrWarn.ctl"/>
				<Item Name="eventvkey.ctl" Type="VI" URL="/&lt;vilib&gt;/event_ctls.llb/eventvkey.ctl"/>
				<Item Name="Find Tag.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Find Tag.vi"/>
				<Item Name="Format Message String.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Format Message String.vi"/>
				<Item Name="General Error Handler Core CORE.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/General Error Handler Core CORE.vi"/>
				<Item Name="General Error Handler.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/General Error Handler.vi"/>
				<Item Name="Get Instrument State.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/victl.llb/Get Instrument State.vi"/>
				<Item Name="Get String Text Bounds.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Get String Text Bounds.vi"/>
				<Item Name="Get Text Rect.vi" Type="VI" URL="/&lt;vilib&gt;/picture/picture.llb/Get Text Rect.vi"/>
				<Item Name="GetHelpDir.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/GetHelpDir.vi"/>
				<Item Name="GetRTHostConnectedProp.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/GetRTHostConnectedProp.vi"/>
				<Item Name="Longest Line Length in Pixels.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Longest Line Length in Pixels.vi"/>
				<Item Name="LVBoundsTypeDef.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/miscctls.llb/LVBoundsTypeDef.ctl"/>
				<Item Name="LVRectTypeDef.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/miscctls.llb/LVRectTypeDef.ctl"/>
				<Item Name="NI_AALBase.lvlib" Type="Library" URL="/&lt;vilib&gt;/Analysis/NI_AALBase.lvlib"/>
				<Item Name="NI_AALPro.lvlib" Type="Library" URL="/&lt;vilib&gt;/Analysis/NI_AALPro.lvlib"/>
				<Item Name="NI_AdvCtrl_continuous linear.lvlib" Type="Library" URL="/&lt;vilib&gt;/addons/control/advanced/NI_AdvCtrl_continuous linear.lvlib"/>
				<Item Name="NI_AdvCtrl_nonlinear.lvlib" Type="Library" URL="/&lt;vilib&gt;/addons/control/advanced/NI_AdvCtrl_nonlinear.lvlib"/>
				<Item Name="NI_Matrix.lvlib" Type="Library" URL="/&lt;vilib&gt;/Analysis/Matrix/NI_Matrix.lvlib"/>
				<Item Name="NI_PID_autopid.lvlib" Type="Library" URL="/&lt;vilib&gt;/addons/control/pid/NI_PID_autopid.lvlib"/>
				<Item Name="NI_PID_pid.lvlib" Type="Library" URL="/&lt;vilib&gt;/addons/control/pid/NI_PID_pid.lvlib"/>
				<Item Name="NI_PtbyPt.lvlib" Type="Library" URL="/&lt;vilib&gt;/ptbypt/NI_PtbyPt.lvlib"/>
				<Item Name="Not Found Dialog.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Not Found Dialog.vi"/>
				<Item Name="Open Panel.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/victl.llb/Open Panel.vi"/>
				<Item Name="PID Online (Relay Feedback).vi" Type="VI" URL="/&lt;vilib&gt;/addons/control/pid/autopid.llb/PID Online (Relay Feedback).vi"/>
				<Item Name="PID Table (Ultimate Gain and Frequency - Ziegler Nichols).vi" Type="VI" URL="/&lt;vilib&gt;/addons/control/pid/autopid.llb/PID Table (Ultimate Gain and Frequency - Ziegler Nichols).vi"/>
				<Item Name="Search and Replace Pattern.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Search and Replace Pattern.vi"/>
				<Item Name="Set Bold Text.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Set Bold Text.vi"/>
				<Item Name="Set String Value.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Set String Value.vi"/>
				<Item Name="Simple Error Handler.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Simple Error Handler.vi"/>
				<Item Name="TagReturnType.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/TagReturnType.ctl"/>
				<Item Name="Three Button Dialog CORE.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Three Button Dialog CORE.vi"/>
				<Item Name="Three Button Dialog.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Three Button Dialog.vi"/>
				<Item Name="Trim Whitespace.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Trim Whitespace.vi"/>
				<Item Name="whitespace.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/whitespace.ctl"/>
			</Item>
			<Item Name="lvanlys.dll" Type="Document" URL="/&lt;resource&gt;/lvanlys.dll"/>
		</Item>
		<Item Name="Build Specifications" Type="Build">
			<Item Name="PID Toolkit Control" Type="EXE">
				<Property Name="App_copyErrors" Type="Bool">true</Property>
				<Property Name="App_INI_aliasGUID" Type="Str">{BB21ED28-FA90-4050-9C0D-443C44F5FD82}</Property>
				<Property Name="App_INI_GUID" Type="Str">{E30FD652-761F-4995-A495-645DE88A3295}</Property>
				<Property Name="App_serverConfig.httpPort" Type="Int">8002</Property>
				<Property Name="Bld_autoIncrement" Type="Bool">true</Property>
				<Property Name="Bld_buildCacheID" Type="Str">{116A54A7-3D34-494E-A791-77E5BA600F08}</Property>
				<Property Name="Bld_buildSpecName" Type="Str">PID Toolkit Control</Property>
				<Property Name="Bld_excludeInlineSubVIs" Type="Bool">true</Property>
				<Property Name="Bld_excludeLibraryItems" Type="Bool">true</Property>
				<Property Name="Bld_excludePolymorphicVIs" Type="Bool">true</Property>
				<Property Name="Bld_localDestDir" Type="Path">../build</Property>
				<Property Name="Bld_localDestDirType" Type="Str">relativeToProject</Property>
				<Property Name="Bld_modifyLibraryFile" Type="Bool">true</Property>
				<Property Name="Bld_previewCacheID" Type="Str">{DFF1E63B-78D7-4E3C-BCAD-156514B2A217}</Property>
				<Property Name="Bld_version.build" Type="Int">3</Property>
				<Property Name="Bld_version.major" Type="Int">1</Property>
				<Property Name="Destination[0].destName" Type="Str">PidToolkitControl.exe</Property>
				<Property Name="Destination[0].path" Type="Path">../build/PidToolkitControl.exe</Property>
				<Property Name="Destination[0].path.type" Type="Str">relativeToProject</Property>
				<Property Name="Destination[0].preserveHierarchy" Type="Bool">true</Property>
				<Property Name="Destination[0].type" Type="Str">App</Property>
				<Property Name="Destination[1].destName" Type="Str">Support Directory</Property>
				<Property Name="Destination[1].path" Type="Path">../build/data</Property>
				<Property Name="Destination[1].path.type" Type="Str">relativeToProject</Property>
				<Property Name="DestinationCount" Type="Int">2</Property>
				<Property Name="Exe_VardepHideDeployDlg" Type="Bool">true</Property>
				<Property Name="Source[0].itemID" Type="Str">{12B9D676-E82E-4515-933A-1D3F361A39FB}</Property>
				<Property Name="Source[0].type" Type="Str">Container</Property>
				<Property Name="Source[1].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[1].itemID" Type="Ref">/My Computer/pid-toolkit.lvlib/pid-toolkit-control.vi</Property>
				<Property Name="Source[1].sourceInclusion" Type="Str">TopLevel</Property>
				<Property Name="Source[1].type" Type="Str">VI</Property>
				<Property Name="Source[2].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[2].itemID" Type="Ref">/My Computer/pid-toolkit-modbus.lvlib</Property>
				<Property Name="Source[2].Library.allowMissingMembers" Type="Bool">true</Property>
				<Property Name="Source[2].type" Type="Str">Library</Property>
				<Property Name="SourceCount" Type="Int">3</Property>
				<Property Name="TgtF_companyName" Type="Str">Geirmundur Orri Sigurdsson</Property>
				<Property Name="TgtF_fileDescription" Type="Str">PID Toolkit Control</Property>
				<Property Name="TgtF_internalName" Type="Str">PID Toolkit Control</Property>
				<Property Name="TgtF_legalCopyright" Type="Str">Copyright © 2020 Geirmundur Orri Sigurdsson</Property>
				<Property Name="TgtF_productName" Type="Str">PID Toolkit Control</Property>
				<Property Name="TgtF_targetfileGUID" Type="Str">{8A99DD0A-E6ED-4D51-AEC1-62BEBA7BECAC}</Property>
				<Property Name="TgtF_targetfileName" Type="Str">PidToolkitControl.exe</Property>
				<Property Name="TgtF_versionIndependent" Type="Bool">true</Property>
			</Item>
		</Item>
	</Item>
</Project>
