/*!
 * @brief	�X�P���g���G�N�X�|�[�^�[�B
 */

pluginManager.loadClass FbxExporter

--�I�u�W�F�N�g�p�����[�^�B
struct ObjectParam(
	localPos,
	localRot ,
	objName,
	bindPose,
	invBindPose,
	parentId,
	n
)
--�A�j���[�V�����L�[�t���[��
struct KeyFrame(
	boneId,
	t,
	localTransform
)
--�A�j���[�V�����N���b�v
struct AnimationClip(
	animClipName,		--�A�j���[�V�����N���b�v��
	keyFrames = #()		--�L�[�t���[���̃��X�g
)
--�I�u�W�F�N�g�p�����[�^�̔z��B
g_objectParams = #()

startFrame = 0
endFrame = 0

rollout tkExporter "tkExporter" width:194 height:248
(
	editText animClipStartFrame "" pos:[91,270] width:58 height:21
	label lbl1 "start frame" pos:[23,273] width:60 height:16
	groupBox grp1 "Animation clip" pos:[13,249] width:145 height:134
	groupBox grp2 "Skeleton" pos:[12,172] width:145 height:64
	button btn_saveAnimationClip "Save" pos:[28,339] width:120 height:28
	label lbl2 "end frame" pos:[23,304] width:60 height:16
	editText animClipEndFrame "" pos:[91,302] width:58 height:21
	button btn_saveSkeleton "Save" pos:[23,191] width:120 height:28
	label lbl3 "Label" pos:[34,291] width:0 height:0
	groupBox grp5 "FBX" pos:[13,13] width:145 height:64
	button btn_save_fbx "Save" pos:[24,33] width:120 height:28
	groupBox grp10 "FBX And Skeleton" pos:[13,92] width:145 height:64
	button btn_save_fbx_and_skeleton "Save" pos:[24,112] width:120 height:28
	
	/*
	 *  �o�͂���m�[�h�̏����\�z�B
	 */
	fn BuildOutputNodeInfo n parentId= 
	(
		objParam = ObjectParam Point3 Quat "" Matrix3 Matrix3 -1 Node
		objParam.objName = n.name
		objParam.bindPose = n.transform
		objParam.invBindPose = inverse n.transform
		objParam.n = n
		if n.parent == undefined then(
			--�e�����Ȃ�
			objParam.parentId = -1
			objParam.localPos = n.pos
			objParam.localRot = n.rotation
			
		)else(
			--�e������
			objParam.parentId = parentId
			objParam.localPos = n.pos * inverse n.parent.transform
			objParam.localRot = n.rotation * inverse n.parent.rotation
		)

		append g_objectParams objParam
		parentId = g_objectParams.count-1
		--�q�����B
		for child in n.children do(
			BuildOutputNodeInfo child parentId
		)
	)
	/*
	 *  �X�P���g���̕ۑ��B
	 */
	fn SaveSkeleton = 
	(
		filepath = getSaveFileName caption:"" types: "skeleton (*tks)|*.tks|All Files (*.*)|*.*|"
		
		if filepath != undefined then
		(
			
			file = fopen filepath "wb"
			
			try(
				--�w�b�_�[���o��
				WriteLong file g_objectParams.count
				
				for o in g_objectParams do (
					
					WriteByte file o.objName.count
					WriteString file o.objName
					WriteLong file o.parentId
					--�o�C���h�|�[�Y���o�́B
					for i = 1 to 4 do(
						WriteFloat file o.bindPose[i].x
						WriteFloat file o.bindPose[i].y
						WriteFloat file o.bindPose[i].z
					)
					--�o�C���h�|�[�Y�̋t�����o�́B
					for i = 1 to 4 do(
						WriteFloat file o.invBindPose[i].x
						WriteFloat file o.invBindPose[i].y
						WriteFloat file o.invBindPose[i].z
					)
				)
			)catch(
				Messagebox "�t�@�C���̕ۑ��Ɏ��s���܂���"
			)
			FClose file
		)
	)
	
	/*
	 *  �A�j���[�V�����N���b�v�̕ۑ��B
	 */
	fn SaveAnimationClip=
	(
		filepath = getSaveFileName caption:"" types: "animation clip (*tka)|*.tka|All Files (*.*)|*.*|"

		if filepath != undefined then
		(
			
			numKey = endFrame - startFrame + 1
			if numKey <= 0 then(
				--1�t���[�������o���B
				endFrame = startFrame
				numKey = 1
			)
			deltaTime = 1.0/30
			keyTime = 0.0
			
			numKey *= g_objectParams.Count
			matTransList = #()
			matRotList = #()

			file = fopen filepath "wb"
			--�w�b�_�[���o��
			WriteLong file numKey
			--�A�j���[�V�����C�x���g�̐����o��
			numNoteTrack = numNoteTracks selection[1]

			if numNoteTrack > 0 then(
				--�m�[�g�L�[�̐����o��
				nt = getNoteTrack selection[1] 1
				WriteLong file nt.keys.count
				for k in nt.keys do(
					--�C�x���g���������鎞�Ԃ��o��
					if k.time >= numKey then(
						exit
					)
					invokeTime = k.time * deltaTime
					
					WriteFloat file invokeTime
					WriteLong file k.value.count
					WriteString file k.value
				)
			)else(
				WriteLong file 0
			)
			
			fclose file
			--�A�j���[�V�����̏����o�́B
			slidertime=startFrame

			file = fopen filepath "ab"
			
			for i=startFrame to endFrame do(
				boneId = 0
				keyTime = (i - startFrame) * deltaTime
				
				for o in g_objectParams do (
					n = o.n

					--�o��
					WriteLong file boneId -- ��ID
					WriteFloat file keyTime -- ����
					
					--�{�[�����[�J���s��ɕϊ�����B
					
					transformMatrix = Matrix3 1
					if n.parent == undefined then(
						transformMatrix =n.transform
					)else(
						transformMatrix = n.transform * inverse n.parent.transform
					)
					for i = 1 to 4 do(
						
						WriteFloat file transformMatrix[i].x
						WriteFloat file transformMatrix[i].y
						WriteFloat file transformMatrix[i].z
					)
					boneId +=1
					
				)
				slidertime += 1
			)
			
			fclose file

		)
	)
	/*
	 *  �X�P���g���̏o�͂̃{�^���������ꂽ�Ƃ��̏����B
	 */
	on btn_saveSkeleton pressed do
	(
		if selection[1] == undefined then(
			Messagebox "�o�͂���X�P���g���̃��[�g�̃I�u�W�F�N�g��I�����ĉ������B�B�B"
		)else(
			g_objectParams = #()
			--�A�j���[�V�������Ԃ�0�ɂ���B
			animationRange = interval 0 animationRange.end
			slidertime = 0
			at time 0(
				--�A�j���[�V�����i�s���̏����B
				BuildOutputNodeInfo selection[1] -1
				SaveSkeleton()
			)
		)
	)
	/*
	 *  �A�j���[�V�����N���b�v�̕ۑ��̃{�^���������ꂽ�Ƃ��̏����B
	 */
	on btn_saveAnimationClip pressed do
	(
		if selection[1] == undefined  then(
			Messagebox "�o�͂���A�j���[�V�����N���b�v���܂ރX�P���g���̃��[�g�̃I�u�W�F�N�g��I�����Ă��������B"
		)else(
			--�Ƃ肠�����S�N���b�v�o�͂���B
			g_objectParams = #()
			--�A�j���[�V�������Ԃ�0�ɂ���B
			startFrame = animClipStartFrame.text as integer
			endFrame = animClipEndFrame.text as integer
			animationRange = interval startFrame endFrame
			slidertimer = 0
			animate on(
				--�A�j���[�V�����i�s���̏����B
				BuildOutputNodeInfo selection[1] -1
				try(
					SaveAnimationClip()
				)catch(
					messageBox "�t�@�C���̕ۑ��Ɏ��s���܂���"
				)
			)
		)
	)
	/*!
	 * @brief	FBX�̕ۑ��̃{�^���������ꂽ�Ƃ��̏����B
	 */
	on btn_save_fbx pressed do
	(
		OpenFbxSetting()
	)
)
addrollout tkExporter style:#(#style_titlebar, #style_sysmenu)