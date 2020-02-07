import Tone from '../node_modules/tone';
import io from '../node_modules/socket.io-client/dist/socket.io';
import '../node_modules/web-audio-recorder-js-webpack/lib/WebAudioRecorder.js';
// import './web-audio-recorder-js-master/lib/WebAudioRecorderMp3.js';


const AudioContext = window.AudioContext || window.webkitAudioContext;

// VARIABLES, SETTINGS

const sampleFilePath = 'static/samples/';
const eventsFilePath = 'static/playerEvents/';


const defaultPreset = {
	signals: [ {
			channel: '/fp_dpli_left_midline',
			ranges: [
				{
					name: 'fp_dpli_left_midline_lead',
					min: 0.51,
					max: 0.7
				},
				{
					name: 'fp_dpli_left_midline_mid',
					min: 0.49,
					max: 0.51
				},
				{
					name: 'fp_dpli_left_midline_lag',
					min: 0.30,
					max: 0.49
				}
			]
		},
		{ 	channel: '/fp_dpli_left_lateral',
			ranges: [
				{
					name: 'fp_dpli_left_lateral_lead',
					min: 0.51,
					max: 0.7
				},
				{
					name: 'fp_dpli_left_lateral_mid',
					min: 0.49,
					max: 0.51
				},
				{
					name: 'fp_dpli_left_lateral_lag',
					min: 0.30,
					max: 0.49
				}
			]
		},
		{ 	channel: '/fp_dpli_right_midline',
			ranges: [
				{
					name: 'fp_dpli_right_midline_lead',
					min: 0.51,
					max: 0.7
				},
				{
					name: 'fp_dpli_right_midline_mid',
					min: 0.49,
					max: 0.51
				},
				{
					name: 'fp_dpli_right_midline_lag',
					min: 0.30,
					max: 0.49
				}
			]
		},
		{ 	channel: '/fp_dpli_right_lateral',
			ranges: [
				{
					name: 'fp_dpli_right_lateral_lead',
					min: 0.51,
					max: 0.7
				},
				{
					name: 'fp_dpli_right_lateral_mid',
					min: 0.49,
					max: 0.51
				},
				{
					name: 'fp_dpli_right_lateral_lag',
					min: 0.30,
					max: 0.49
				}
			]
		},
		{ 	channel: '/fp_wpli_left_midline',
			ranges: [
				{
					name: 'fp_wpli_left_midline',
					min: 0.03,
					max: 0.4
				}
			]
		},
		{ 	channel: '/fp_wpli_left_lateral',
			ranges: [
				{
					name: 'fp_wpli_left_lateral',
					min: 0.03,
					max: 0.4
				}
			]
		},
		{ 	channel: '/fp_wpli_right_midline',
			ranges: [
				{
					name: 'fp_wpli_right_midline',
					min: 0.03,
					max: 0.4
				}
			]
		},
		{ 	channel: '/fp_wpli_right_lateral',
			ranges: [
				{
					name: 'fp_wpli_right_lateral',
					min: 0.03,
					max: 0.4
				}
			]
		},
		{ 	channel: '/hl_relative_position',
			ranges: [
				{
					name: 'hl_front',
					min: 0.,
					max: 0.6
				},
				{
					name: 'hl_back',
					min: 0.5,
					max: 1
				}
			]
		},
		{ 	channel: '/pe_frontal',
			ranges: [
				{
					name: 'pe_frontal_rel',
					relative: true,				
				},
				{	name: 'pe_frontal_abs',
					min: 0.4,
					max: 1
				},
				{	name: 'pe_frontal_diff',
					min: -1,
					max: 1
				}
			]
		},
		{ 	channel: '/pe_parietal',
			ranges: [
				{
					name: 'pe_parietal_rel',
					relative: true,
				},
				{	name: 'pe_parietal_abs',
					min: 0.4,
					max: 1
				}
			]
		},
		{ 	channel: '/pac_rpt_frontal',
			ranges: []
		},
		{ 	channel: '/pac_rpt_parietal',
			ranges: []
		},
		{ 	channel: '/spr_beta_alpha',
			ranges: [
				{
					name: 'spr_beta_alpha_gloc',
					min: -2,
					max: -1,
				},
				{
					name: 'spr_beta_alpha_full',
					min: -1.5,
					max: 1.5,
				},
				{
					name: 'spr_beta_alpha_high',
					min: 0,
					max: 2
				}
			]
		},
		{ 	channel: '/spr_alpha_theta',
			ranges: [
				{
					name: 'spr_alpha_theta_fullrange',
					min: -1.5,
					max: 1.5
				},
				{
					name: 'spr_alpha_theta_relative',
					min: -0.6,
					max: -0.4,
					relative: true,
					value: 'avg3'
				},

			]
		},
		{ 	channel: '/td_front_back',
			ranges: [
				{
					name: 'td_front_back',
					min: 0.9,
					max: 1.1,
				}
			]
		}
	],
	tracks: [
	{	fileName: 'harp_main.ogg',
		gain: -2,
		loopLength: 5,
		decayCutoff: 0.1,
		inputs: [{ 	range:'spr_alpha_theta_fullrange',
					type:'loopPoint',
					value:'avg5',
					min: 0.2,
					peak: 0.45,
					max: 0.45,
					decayBoost: 0.3,
					decayRate: 0.4,
					decayRange: 0.15
				},
				{ 	range:'spr_alpha_theta_fullrange',
					type:'volume',
					value:'avg3',
					min: 0.2,
					peak: 0.4,
					max: 0.6,
					decayRate: 0.4,
					decayRange: 0.15
				}
				]
	},
	{	fileName: 'harp_melody.ogg',
		gain: -2,
		loopLength: 5,
		decayCutoff: 0.1,
		inputs: [{ 	range:'spr_alpha_theta_fullrange',
					type:'loopPoint',
					value:'avg5',
					min: 0.2,
					peak: 0.45,
					max: 0.45,
					decayBoost: 0.3,
					decayRate: 0.7,
					decayRange: 0.15
				},
				{ 	range:'spr_alpha_theta_fullrange',
					type:'volume',
					value:'diff5',
					min: 0.5,
					peak: 0.75,
					max: 0.75,
					decayRate: 0.5,
					decayRange: 0.15
				}
				]
	},
	{	fileName: 'pianoascending.ogg',
		gain: -5,
		loopLength: 5,
		decayCutoff: 0.1,
		inputs: [{ 	range:'spr_alpha_theta_fullrange',
					type:'loopPoint',
					value:'avg5',
					min: 0.4,
					peak: 0.8,
					max: 0.8,
					decayBosst: 0.25,
					decayRate: 0.5,
					decayRange: 0.15 },
				{ 	range:'spr_alpha_theta_fullrange',
					type:'volume',
					value:'avg3',
					min: 0.4,
					peak: 0.6,
					max: 0.8,
					decayBosst: 0.25,
					decayRate: 0.4,
					decayRange: 0.15 }
				]
	},
	{	fileName: 'rhodes.ogg',
		gain: -10,
		loopLength: 5,
		decayCutoff: 0.1,
		inputs: [{ 	range:'spr_alpha_theta_fullrange',
					type:'loopPoint',
					value:'avg5',
					min: 0.6,
					peak: 1,
					max: 1,
					decayRate: 0.5,
					decayRange: 0.15 },
				{ 	range:'spr_alpha_theta_fullrange',
					type:'volume',
					value:'avg3',
					min: 0.6,
					peak: 0.8,
					max: 1,
					decayRate: 0.4,
					decayRange: 0.15 }
				]
	},
	// { 	fileName: 'synthwithtriangleampmod.ogg',
	// 	gain: -5,
	// 	loopLength: 4,
	// 	decayCutoff: 0.2,
	// 	inputs: [{	range:'spr_beta_alpha_full',
	// 				type:'volume',
	// 				value: 'avg3',
	// 				min: 0.2,
	// 				peak: 0.4,
	// 				max: 0.6,
	// 				decayBoost: 0.3,
	// 				decayRate: 0.5,
	// 				decayRange: 0.2 },
	// 			{	range:'spr_beta_alpha_full',
	// 				type:'loopPoint',
	// 				value: 'avg3',
	// 				min: 0.2,
	// 				peak: 0.6,
	// 				max: 0.6,
	// 				decayBoost: 0.3,
	// 				decayRate: 0.5,
	// 				decayRange: 0.2 }
	// 			]
	// },
	{ 	fileName: 'softersynth.ogg',
		gain: -5,
		loopLength: 4,
		decayCutoff: 0.2,
		inputs: [{	range:'spr_beta_alpha_full',
					type:'loopPoint',
					value: 'avg3',
					min: 0.2,
					peak: 0.8,
					max: 0.8,
					decayBoost: 0.3,
					decayRate: 0.4,
					decayRange: 0.15 },
				{	range:'spr_beta_alpha_full',
					type:'volume',
					value: 'avg3',
					min: 0.2,
					peak: 0.5,
					max: 0.8,
					decayBoost: 0.3,
					decayRate: 0.4,
					decayRange: 0.15 }
				]
	},

	{	fileName: 'slow_gloc_melody.ogg',
		gain: -10,
		inputs: [{	range: 'spr_beta_alpha_full',
					type: 'volume',
					value: 'curr',
					min: 0,
					peak: 0.1,
					max: 0.2,
					decayRate: 0.7,
					decayRange: 0.2
		}]
	},
	{
		fileName: 'flutedrone.ogg',
		gain: -12,
		decayCutoff: 0.2,
		inputs: [{	range: 'hl_front',
					type: 'volume',
					value: 'avg5',
					min: 0,
					peak: .3,
					max: 0.7,
					decayRate: 0.6,
					decayRange: 0.2
				}
			]
	},
	{
		fileName: 'thindrone.ogg',
		gain: -8,
		decayCutoff: 0.2,
		inputs: [{	range: 'hl_front',
					type: 'volume',
					value: 'avg5',
					min: 0.5,
					peak: 0.8,
					max: 1,
					decayRate: 0.6,
					decayRange: 0.4,
					decayBoost: 0.2,
				}
			]
	},
	{
		fileName: 'HL-cello.ogg',
		gain: -15,
		decayCutoff: 0.2,
		inputs: [{	range: 'hl_back',
					type: 'volume',
					value: 'avg5',
					min: 0,
					peak: 0.5,
					max: 1,
					decayRate: 0.3,
					decayRange: 0.3,
					decayBoost: 0.15
				}
			]
	},
		{
		fileName: 'HL-viola.ogg',
		gain: -15,
		decayCutoff: 0.2,
		inputs: [{	range: 'hl_back',
					type: 'volume',
					value: 'avg5',
					min: 0.25,
					peak: 0.66,
					max: 1,
					decayRate: 0.3,
					decayRange: 0.3,
					decayBoost: 0.15
				}
			]
	},	{
		fileName: 'HL-violin2.ogg',
		gain: -15,
		decayCutoff: 0.2,
		inputs: [{	range: 'hl_back',
					type: 'volume',
					value: 'avg5',
					min: 0.33,
					peak: 0.75,
					max: 1,
					decayRate: 0.3,
					decayRange: 0.3,
					decayBoost: 0.15
				}
			]
	},	{
		fileName: 'HL-violin1.ogg',
		gain: -15,
		decayCutoff: 0.2,
		inputs: [{	range: 'hl_back',
					type: 'volume',
					value: 'avg5',
					min: 0.5,
					peak: 0.8,
					max: 1,
					decayRate: 0.3,
					decayRange: 0.3,
					decayBoost: 0.15
				}
			]
	},
	{
		fileName: 'PE-drum.ogg',
		gain: -5,
		decayCutoff: 0.1,
		inputs: [{	range: 'pe_frontal_rel',
					type: 'volume',
					value: 'curr',
					min: 0.4,
					peak: 1,
					max: 1,
					decayRate: 0.5,
					decayRange: 0.15,
					decayBoost: 0.5
		},
		{			range: 'pe_frontal_rel',
					type: 'playbackRate',
					value: 'avg3',
					playbackMin: 0.6,
					playbackSpeedup: 2,
					min: 0.7,
					peak: 1,
					max: 1,
					decayRate: 0.5,
					decayRange: 0.15,
					decayBoost: 0.5
		}
		]
	},
	{
		fileName: 'PE-kick.ogg',
		gain: -5,
		decayCutoff: 0.1,
		inputs: [{	range: 'pe_frontal_rel',
					type: 'volume',
					value: 'curr',
					min: 0.5,
					peak: 1,
					max: 1,
					decayRate: 0.5,
					decayRange: 0.15,
					decayBoost: 0.2
		},
		{			range: 'pe_frontal_rel',
					type: 'playbackRate',
					value: 'avg3',
					playbackMin: 0.6,
					playbackSpeedup: 2,
					min: 0.7,
					peak: 1,
					max: 1,
					decayRate: 0.5,
					decayRange: 0.15,
					decayBoost: 0.5
		}
		]
	},
	{
		fileName: 'PE-hi-hat.ogg',
		gain: -5,
		decayCutoff: 0.1,
		inputs: [{	range: 'pe_parietal_rel',
					type: 'volume',
					value: 'curr',
					min: 0.5,
					peak: 1,
					max: 1,
					decayRate: 0.5,
					decayRange: 0.15,
					decayBoost: 0.2
		},
		{			range: 'pe_frontal_rel',
					type: 'playbackRate',
					value: 'avg3',
					playbackMin: 0.6,
					playbackSpeedup: 2,
					min: 0.7,
					peak: 1,
					max: 1,
					decayRate: 0.5,
					decayRange: 0.15,
					decayBoost: 0.5
		}]
	},	
	{
		fileName: 'PE-tambourine.ogg',
		gain: -5,
		decayCutoff: 0.1,
		inputs: [{	range: 'pe_frontal_rel',
					type: 'volume',
					value: 'curr',
					min: 0.7,
					peak: 1,
					max: 1,
					decayRate: 0.5,
					decayRange: 0.15,
					decayBoost: 0.2
			},
		{			range: 'pe_frontal_rel',
					type: 'playbackRate',
					value: 'avg3',
					playbackMin: 0.6,
					playbackSpeedup: 2,
					min: 0.7,
					peak: 1,
					max: 1,
					decayRate: 0.5,
					decayRange: 0.15,
					decayBoost: 0.5
		}
		]
	},	
	{
		fileName: 'PE-cymbal.ogg',
		gain: -5,
		decayCutoff: 0.1,
		inputs: [{	range: 'pe_parietal_rel',
					type: 'volume',
					value: 'curr',
					min: 0.7,
					peak: 1,
					max: 1,
					decayRate: 0.5,
					decayRange: 0.15,
					decayBoost: 0.2
		},
		{			range: 'pe_frontal_rel',
					type: 'playbackRate',
					value: 'avg3',
					playbackMin: 0.6,
					playbackSpeedup: 2,
					min: 0.,
					peak: 1,
					max: 1,
					decayRate: 0.5,
					decayRange: 0.15,
					decayBoost: 0.5
		}]
	},
	{
		fileName: 'PE-noise.ogg',
		gain: -20,
		decayCutoff: 0.1,
		inputs: [{	range: 'pe_frontal_abs',
					type: 'volume',
					value: 'avg3',
					min: 0,
					peak: 0.8,
					max: 1,
					decayRate: 0.5,
					decayRange: 0.15,
					decayBoost: 0.2
		}]
	},
	{	fileName: 'PE-noise2.ogg',
		gain: -20,
		decayCutoff: 0.1,
		inputs: [{	range: 'pe_parietal_abs',
					type: 'volume',
					value: 'avg3',
					min: 0.0,
					peak: 0.8,
					max: 1,
					decayRate: 0.5,
					decayRange: 0.15,
					decayBoost: 0.2
		}]
	},
	{	fileName: 'expanseloop.ogg',
		gain: -20,
		decayCutoff: 0.1,
		inputs: [{	range: 'pe_frontal_abs',
					type: 'volume',
					value: 'avg3',
					min: 0.0,
					peak: 1,
					max: 1,
					decayRate: 0.7,
					decayRange: 0.1,
					decayBoost: 0.2
		}]
	},
	{	fileName: 'microtwinkle.ogg',
		gain: -10,
		loopLength: 4,
		decayCutoff: 0.15,
		inputs: [{	range:'pe_frontal_abs',
					type: 'volume',
					value: 'curr',
					min: 0.85,
					peak: 1,
					max: 1,
					decayBoost: 0.3,
					decayRate: 0.4,
					decayRange: 0.25
				},
				{	range:'pe_frontal_abs',
					type: 'loopPoint',
					value: 'avg3',
					min: 0,
					peak: 0.75,
					max: 1,
					decayBoost: 0.4,
					decayRate: 0.4,
					decayRange: 0.25

				}
			]
	},
	{	fileName: 'TD-synthwithfilters.ogg',
		gain: -18,
		loopLength: 0.75,
		decayCutoff: 0.15,
		inputs: [
				// {	range:'td_front_back',
				// 	type: 'volume',
				// 	value: 'curr',
				// 	min: 0.85,
				// 	peak: 1,
				// 	max: 1,
				// 	decayBoost: 0.3,
				// 	decayRate: 0.4,
				// 	decayRange: 0.25
				// },
				{	range:'td_front_back',
					type: 'loopPoint',
					value: 'avg3',
					min: 0,
					peak: 1,
					max: 1,
					decayBoost: 0.3,
					decayRate: 0.6,
					decayRange: 0.25

				}
			]
	},


	// values of dPLI that are less than 0.5 - these are the ones that indicate consciousness
	{	fileName: 'dpliLLconscious.ogg',
		gain: -2,
		loopLength: 1.5,
		decayCutoff: 0.1,
		inputs: [{ 	range:'fp_dpli_left_lateral_lag',
					type:'loopPoint',
					value: 'curr',
					min: 0.5,
					peak: 0.5,
					max: 1,
					decayBoost: 0.5,
					decayRate: 0.6,
					decayRange: 0.1 },
				{ 	range:'fp_dpli_left_lateral_lag',
					type:'volume',
					value: 'curr',
					min: 0.8,
					peak: 0.8,
					max: 1,
					decayBoost: 0.5,
					decayRate: 0.6,
					decayRange: 0.1 },
				{ 	range:'fp_wpli_left_lateral',
					type:'volume',
					value: 'curr',
					min: 0,
					peak: 1,
					max: 1,
					decayBoost: 0.5,
					decayRate: 0.6,
					decayRange: 0.1 }
				]
	},
	{	fileName: 'dpliLMconscious.ogg',
		gain: -2,
		loopLength: 1.5,
		decayCutoff: 0.1,
		inputs: [{ 	range:'fp_dpli_left_midline_lag',
					type:'loopPoint',
					value: 'curr',
					min: 0.5,
					peak: 0.5,
					max: 1,
					decayBoost: 0.5,
					decayRate: 0.6,
					decayRange: 0.1 },
				{ 	range:'fp_dpli_left_midline_lag',
					type:'volume',
					value: 'curr',
					min: 0.8,
					peak: 0.8,
					max: 1,
					decayBoost: 0.5,
					decayRate: 0.6,
					decayRange: 0.1 },
				{ 	range:'fp_wpli_left_midline',
					type:'volume',
					value: 'curr',
					min: 0,
					peak: 1,
					max: 1,
					decayBoost: 0.5,
					decayRate: 0.6,
					decayRange: 0.1 }
				]
	},
	{	fileName: 'dpliRMconscious.ogg',
		gain: -2,
		loopLength: 1.5,
		decayCutoff: 0.1,
		inputs: [{ 	range:'fp_dpli_right_midline_lag',
					type:'loopPoint',
					value: 'curr',
					min: 0.5,
					peak: 0.5,
					max: 1,
					decayBoost: 0.5,
					decayRate: 0.6,
					decayRange: 0.1 },
				{ 	range:'fp_dpli_right_midline_lag',
					type:'volume',
					value: 'curr',
					min: 0.8,
					peak: 0.8,
					max: 1,

					decayBoost: 0.5,
					decayRate: 0.6,
					decayRange: 0.1 },
				{ 	range:'fp_wpli_right_midline',
					type:'volume',
					value: 'curr',
					min: 0,
					peak: 1,
					max: 1,
					decayBoost: 0.5,
					decayRate: 0.6,
					decayRange: 0.1 }
				]
	},
	{	fileName: 'dpliRLconscious.ogg',
		gain: -2,
		loopLength: 1.5,
		decayCutoff: 0.1,
		inputs: [{ 	range:'fp_dpli_right_lateral_lag',
					type:'loopPoint',
					value: 'curr',
					min: 0.5,
					peak: 0.5,
					max: 1,
					decayBoost: 0.5,
					decayRate: 0.6,
					decayRange: 0.1 },
				{ 	range:'fp_dpli_right_lateral_lag',
					type:'volume',
					value: 'curr',
					min: 0.8,
					peak: 0.8,
					max: 1,
					decayBoost: 0.5,
					decayRate: 0.6,
					decayRange: 0.1 },
				{ 	range:'fp_wpli_right_lateral',
					type:'volume',
					value: 'curr',
					min: 0,
					peak: 1,
					max: 1,
					decayBoost: 0.5,
					decayRate: 0.6,
					decayRange: 0.1 }
				]
	},

	//  phase-lead values of dPLI
	{	fileName: 'dpliLL_lead.ogg',
		gain: -5,
		loopLength: 1.5,
		decayCutoff: 0.1,
		inputs: [{ 	range:'fp_dpli_left_lateral_lead',
					type:'loopPoint',
					value: 'curr',
					min: 0,
					peak: 1,
					max: 1,
					decayRate: 0.6,
					decayRange: 0.1 },
				{ 	range:'fp_dpli_left_lateral_lead',
					type:'volume',
					value: 'curr',
					min: 0,
					peak: 0.2,
					max: 0.2,
					decayBoost: 0.5,
					decayRate: 0.6,
					decayRange: 0.1 },
				{ 	range:'fp_wpli_left_lateral',
					type:'volume',
					value: 'curr',
					min: 0,
					peak: 1,
					max: 1,
					decayRate: 0.6,
					decayRange: 0.1 }
				]
	},
	{	fileName: 'dpliLM_lead.ogg',
		gain: -5,
		loopLength: 1.5,
		decayCutoff: 0.1,
		inputs:[{ 	range:'fp_dpli_left_midline_lead',
					type:'loopPoint',
					value: 'curr',
					min: 0,
					peak: 1,
					max: 1,
					decayRate: 0.6,
					decayRange: 0.1 },
				{ 	range:'fp_dpli_left_midline_lead',
					type:'volume',
					value: 'curr',
					min: 0,
					peak: 0.2,
					max: 0.2,
					decayBoost: 0.5,
					decayRate: 0.6,
					decayRange: 0.1 },
				{ 	range:'fp_wpli_left_midline',
					type:'volume',
					value: 'curr',
					min: 0,
					peak: 1,
					max: 1,
					decayRate: 0.6,
					decayRange: 0.1 }
				]
	},
	{	fileName: 'dpliRM_lead.ogg',
		gain: -5,
		loopLength: 1.5,
		decayCutoff: 0.1,
		inputs: [{ 	range:'fp_dpli_right_midline_lead',
					type:'loopPoint',
					value: 'curr',
					min: 0,
					peak: 1,
					max: 1,
					decayRate: 0.6,
					decayRange: 0.1 },
				{ 	range:'fp_dpli_right_midline_lead',
					type:'volume',
					value: 'curr',
					min: 0,
					peak: 0.2,
					max: 0.2,
					decayBoost: 0.5,
					decayRate: 0.6,
					decayRange: 0.1 },
				{ 	range:'fp_wpli_right_midline',
					type:'volume',
					value: 'curr',
					min: 0,
					peak: 1,
					max: 1,
					decayRate: 0.6,
					decayRange: 0.1 }
				]
	},
	{	fileName: 'dpliRL_lead.ogg',
		gain: -5,
		loopLength: 1.5,
		decayCutoff: 0.1,
		inputs: [{ 	range:'fp_dpli_right_lateral_lead',
					type:'loopPoint',
					value: 'curr',
					min: 0,
					peak: 1,
					max: 1 ,
					decayRate: 0.6,
					decayRange: 0.1},
				{ 	range:'fp_dpli_right_lateral_lead',
					type:'volume',
					value: 'curr',
					min: 0,
					peak: 0.2,
					max: 0.2,
					decayBoost: 0.5,
					decayRate: 0.6,
					decayRange: 0.1 },
				{ 	range:'fp_wpli_right_lateral',
					type:'volume',
					value: 'curr',
					min: 0,
					peak: 1,
					max: 1,
					decayRate: 0.6,
					decayRange: 0.1 }
				]
	},
	{
		fileName: 'wPLI-LL-flute-high.ogg',
		gain: -2,
		decayCutoff: 0.2,
		inputs: [{	range: 'fp_wpli_left_lateral',
					type: 'volume',
					value: 'avg3',
					min: 0,
					peak: 1,
					max: 1,
					decayThreshold: 0.4,
					decayBoost: 0.1,
					decayRate: 0.4,
					decayRange: 0.2
				},
				{	range: 'fp_dpli_left_lateral_lag',
					type: 'volume',
					value: 'avg3',
					min: 0.8,
					peak: 0.8,
					max: 1,
					decayThreshold: 0.4,
					decayBoost: 0.1,
					decayRate: 0.4,
					decayRange: 0.2
				}
			]
	},
	{
		fileName: 'wPLI-LL-flute-mid.ogg',
		gain: -10,
		decayCutoff: 0.2,
		inputs: [{	range: 'fp_wpli_left_lateral',
					type: 'volume',
					value: 'avg3',
					min: 0,
					peak: 1,
					max: 1,
					decayThreshold: 0.4,
					decayBoost: 0.1,
					decayRate: 0.4,
					decayRange: 0.2
				},
				{	range: 'fp_dpli_left_lateral_mid',
					type: 'volume',
					value: 'avg3',
					min: 0.3,
					peak: 0.5,
					max: 0.7,
					decayThreshold: 0.4,
					decayBoost: 0.1,
					decayRate: 0.4,
					decayRange: 0.2
				}
			]
	},
	// {
	// 	fileName: 'wPLI-LL-flute-low.ogg',
	// 	gain: -10,
	// 	decayCutoff: 0.2,
	// 	inputs: [{	range: 'fp_wpli_left_lateral',
	// 				type: 'volume',
	// 				value: 'avg3',
	// 				min: 0,
	// 				peak: 1,
	// 				max: 1,
	// 				decayThreshold: 0.4,
	// 				decayBoost: 0.1,
	// 				decayRate: 0.4,
	// 				decayRange: 0.2
	// 			},
	// 			{	range: 'fp_dpli_left_lateral_lead',
	// 				type: 'volume',
	// 				value: 'avg3',
	// 				min: 0,
	// 				peak: 0.2,
	// 				max: 0.2,
	// 				decayThreshold: 0.4,
	// 				decayBoost: 0.1,
	// 				decayRate: 0.4,
	// 				decayRange: 0.2
	// 			}
	// 		]
	// },
	{
		fileName: 'wPLI-LM-bassoon-high.ogg',
		gain: -2,
		decayCutoff: 0.2,
		inputs: [{	range: 'fp_wpli_left_midline',
					type: 'volume',
					value: 'avg3',
					min: 0,
					peak: 1,
					max: 1,
					decayThreshold: 0.4,
					decayBoost: 0.1,
					decayRate: 0.4,
					decayRange: 0.2
				},
				{	range: 'fp_dpli_left_midline_lag',
					type: 'volume',
					value: 'avg3',
					min: 0.8,
					peak: 0.8,
					max: 1,
					decayThreshold: 0.4,
					decayBoost: 0.1,
					decayRate: 0.4,
					decayRange: 0.2
				}
			]
	},
	{
		fileName: 'wPLI-LM-bassoon-mid.ogg',
		gain: -7,
		decayCutoff: 0.2,
		inputs: [{	range: 'fp_wpli_left_midline',
					type: 'volume',
					value: 'avg3',
					min: 0,
					peak: 1,
					max: 1,
					decayThreshold: 0.4,
					decayBoost: 0.1,
					decayRate: 0.4,
					decayRange: 0.2
				},
				{	range: 'fp_dpli_left_midline_mid',
					type: 'volume',
					value: 'avg3',
					min: 0.3,
					peak: 0.5,
					max: 0.7,
					decayThreshold: 0.4,
					decayBoost: 0.1,
					decayRate: 0.4,
					decayRange: 0.2
				}
			]
	},
	// {
	// 	fileName: 'wPLI-LM-bassoon-low.ogg',
	// 	gain: -7,
	// 	decayCutoff: 0.2,
	// 	inputs: [{	range: 'fp_wpli_left_midline',
	// 				type: 'volume',
	// 				value: 'avg3',
	// 				min: 0,
	// 				peak: 1,
	// 				max: 1,
	// 				decayThreshold: 0.4,
	// 				decayBoost: 0.1,
	// 				decayRate: 0.4,
	// 				decayRange: 0.2
	// 			},
	// 			{	range: 'fp_dpli_left_midline_lead',
	// 				type: 'volume',
	// 				value: 'avg3',
	// 				min: 0,
	// 				peak: 0.2,
	// 				max: 0.2,
	// 				decayThreshold: 0.4,
	// 				decayBoost: 0.1,
	// 				decayRate: 0.4,
	// 				decayRange: 0.2
	// 			}
	// 		]
	// },
	{
		fileName: 'wPLI-RM-horn-high.ogg',
		gain: -2,
		decayCutoff: 0.2,
		inputs: [{	range: 'fp_wpli_right_midline',
					type: 'volume',
					value: 'avg3',
					min: 0,
					peak: 1,
					max: 1,
					decayThreshold: 0.4,
					decayBoost: 0.1,
					decayRate: 0.4,
					decayRange: 0.2
				},
				{	range: 'fp_dpli_right_midline_lag',
					type: 'volume',
					value: 'avg3',
					min: 0.8,
					peak: 0.8,
					max: 1,
					decayThreshold: 0.4,
					decayBoost: 0.1,
					decayRate: 0.4,
					decayRange: 0.2
				}
			]
	},
	{
		fileName: 'wPLI-RM-horn-mid.ogg',
		gain: -10,
		decayCutoff: 0.2,
		inputs: [{	range: 'fp_wpli_right_midline',
					type: 'volume',
					value: 'avg3',
					min: 0,
					peak: 1,
					max: 1,
					decayThreshold: 0.4,
					decayBoost: 0.1,
					decayRate: 0.4,
					decayRange: 0.2
				},
				{	range: 'fp_dpli_right_midline_mid',
					type: 'volume',
					value: 'avg3',
					min: 0.3,
					peak: 0.5,
					max: 0.7,
					decayThreshold: 0.4,
					decayBoost: 0.1,
					decayRate: 0.4,
					decayRange: 0.2
				}
			]
	},
	// {
	// 	fileName: 'wPLI-RM-horn-low.ogg',
	// 	gain: -10,
	// 	decayCutoff: 0.2,
	// 	inputs: [{	range: 'fp_wpli_right_midline',
	// 				type: 'volume',
	// 				value: 'avg3',
	// 				min: 0,
	// 				peak: 1,
	// 				max: 1,
	// 				decayThreshold: 0.4,
	// 				decayBoost: 0.1,
	// 				decayRate: 0.4,
	// 				decayRange: 0.2
	// 			},
	// 			{	range: 'fp_dpli_right_midline_lead',
	// 				type: 'volume',
	// 				value: 'avg3',
	// 				min: 0,
	// 				peak: 0.2,
	// 				max: 0.2,
	// 				decayThreshold: 0.4,
	// 				decayBoost: 0.1,
	// 				decayRate: 0.4,
	// 				decayRange: 0.2
	// 			}
	// 		]
	// },
	{
		fileName: 'wPLI-RL-clarinet-high.ogg',
		gain: -2,
		decayCutoff: 0.2,
		inputs: [{	range: 'fp_wpli_right_lateral',
					type: 'volume',
					value: 'avg3',
					min: 0,
					peak: 1,
					max: 1,
					decayThreshold: 0.4,
					decayBoost: 0.1,
					decayRate: 0.4,
					decayRange: 0.2
				},
				{	range: 'fp_dpli_right_lateral_lag',
					type: 'volume',
					value: 'avg3',
					min: 0.8,
					peak: 0.8,
					max: 1,
					decayThreshold: 0.4,
					decayBoost: 0.1,
					decayRate: 0.4,
					decayRange: 0.2
				}
			]
	},
	{
		fileName: 'wPLI-RL-clarinet-mid.ogg',
		gain: -10,
		decayCutoff: 0.2,
		inputs: [{	range: 'fp_wpli_right_lateral',
					type: 'volume',
					value: 'avg3',
					min: 0,
					peak: 1,
					max: 1,
					decayThreshold: 0.4,
					decayBoost: 0.1,
					decayRate: 0.4,
					decayRange: 0.2
				},
				{	range: 'fp_dpli_right_lateral_mid',
					type: 'volume',
					value: 'avg3',
					min: 0.3,
					peak: 0.5,
					max: 0.7,
					decayThreshold: 0.4,
					decayBoost: 0.1,
					decayRate: 0.4,
					decayRange: 0.2
				}
			]
	},
	// {
	// 	fileName: 'wPLI-RL-clarinet-low.ogg',
	// 	gain: -10,
	// 	decayCutoff: 0.2,
	// 	inputs: [{	range: 'fp_wpli_right_midline',
	// 				type: 'volume',
	// 				value: 'avg3',
	// 				min: 0,
	// 				peak: 1,
	// 				max: 1,
	// 				decayThreshold: 0.4,
	// 				decayBoost: 0.1,
	// 				decayRate: 0.4,
	// 				decayRange: 0.2
	// 			},
	// 			{	range: 'fp_dpli_right_midline_lead',
	// 				type: 'volume',
	// 				value: 'avg3',
	// 				min: 0,
	// 				peak: 0.2,
	// 				max: 0.2,
	// 				decayThreshold: 0.4,
	// 				decayBoost: 0.1,
	// 				decayRate: 0.4,
	// 				decayRange: 0.2
	// 			}
	// 		]
	// }
	]
}


// GLOBAL VARIABLES
const sound = {
	context : null,
	masterGain : null,
	tracks : [],
	signals: {}
}


// CLASSES

// Signal are the collection of messags on a range, each also has an associated DOM element
// A channel is the message address - /spr_beta_alpha or /pe_frontal, etc.
class Signal {
	constructor (signal) {
		this.channel = signal.channel;
		this.min = null;
		this.max = null;
		this.curr = 0;
		this.prev = null;
		this.mute = false;
		this.avg3 = 0;
		this.avg5 = 0;
		this.avg10 = 0;
		this.diff3 = 0;
		this.diff5 = 0;
		this.diff10 = 0;
		this.diff3_10 = 0;
		this.last10 = [];
		this.ranges = {}

		signal.ranges.forEach(range => {
			this.ranges[range.name] = new Range(range);
		});

		let signalListGUI = document.getElementById('signalContainer');

		// create the right-side pannel of signals
		this.signalGUI = document.createElement('div');
		this.signalGUI.innerHTML = `<div>${this.channel}</div>`
		let signalTableGUI = document.createElement('table');
		signalTableGUI.innerHTML = `<tr><td>min</td><td>curr</td><td>max</td><td>avg3</td><td>avg5</td><td>avg10</td>`
		this.signalTableRow = document.createElement('tr');

		this.minGUI = this.createGUI();
		this.currGUI = this.createGUI();
		this.currGUI.classList.add('currentValue');
		this.maxGUI = this.createGUI();
		this.avg3GUI = this.createGUI();
		this.avg5GUI = this.createGUI();
		this.avg10GUI = this.createGUI();

		signalTableGUI.appendChild(this.signalTableRow);
		let signalBox = document.createElement('div');
		signalBox.classList.add('signalBox')

		signalBox.appendChild(this.signalGUI);
		signalBox.appendChild(signalTableGUI);

		signalListGUI.appendChild(signalBox);
	}

	createGUI () {
		let gui = document.createElement('td');
		gui.innerText = '';
		this.signalTableRow.appendChild(gui);
		return gui;
	}

	static processMessage(message) {
		// This function is the first step in processing an incoming message. 
		// It does the things that apply to the piece as a whole before passing it on
		// to modify each track one-by-one.

		let messageIn = JSON.parse(JSON.stringify(message)); // fix problem w aliasing

		// This is taking the log 10 of the spectral power ratios, this makes a nicer signal to sonify
		if (messageIn.address === '/spr_beta_alpha' || messageIn.address === '/spr_alpha_theta') {
			messageIn.args[0] = Math.log10(messageIn.args[0]);
		}
		sound.signals[messageIn.address].update(messageIn);

		// This is setting the threshold of a low-pass filter, depending on the TD.
		if (messageIn.address === '/td_front_back') {
			let newFrequency = Math.pow(sound.signals['/td_front_back'].avg5,5) * 8000
			if (newFrequency > 800) {
				sound.filter.frequency.linearRampToValueAtTime(newFrequency, 10);
			} else {
				sound.filter.frequency.linearRampToValueAtTime(800, 10);
			}
		}

		// Send the transformed message to each track.
		Track.processMessage(messageIn);
	}

	static getChannel(rangeName) {
		// takes a string rangeName and returns the channel that has that range
		for (const signal in sound.signals) {
			for (const range in sound.signals[signal].ranges ) {
				if (rangeName === range) {
					return signal;
				}
			}
		}

		return 'not found';
	}

	update (message) {
		// update last 10 messages
		if (this.last10.length == 10) { this.last10.shift(); }
		this.last10.push(message.args[0]);

		if (this.max === null || message.args[0] > this.max) {this.max = message.args[0]}
		if (this.min === null || message.args[0] < this.min) {this.min = message.args[0]}

		this.prev = this.curr;
		this.curr = message.args[0];

		this.diff3 = this.curr - this.avg3;
		this.diff5 = this.curr - this.avg5;
		this.diff10 = this.curr - this.avg10;

		this.avg3 = this.last10.slice(-3).reduce((a,c)=>{return a+c})/this.last10.slice(-3).length;
		this.avg5 = this.last10.slice(-5).reduce((a,c)=>{return a+c})/this.last10.slice(-5).length;
		this.avg10 = this.last10.slice(-10).reduce((a,c)=>{return a+c})/this.last10.slice(-10).length;

		this.diff3_10 = this.avg3 - this.avg10;

		// update ranges
		for (const range in this.ranges) {
			this.ranges[range].update();
		}

		this.display();
	}

	display () {
		this.maxGUI.innerText = this.max.toFixed(3);
		this.minGUI.innerText = this.min.toFixed(3);
		this.currGUI.innerText = this.curr.toFixed(3);
		this.avg3GUI.innerText = this.avg3.toFixed(3);
		this.avg5GUI.innerText = this.avg5.toFixed(3);
		this.avg10GUI.innerText = this.avg10.toFixed(3);
	}

}

// A single track manages playback of a single soundfile.
class Track {
	constructor (track) {

		this.fileName = track.fileName;
		this.inputs = [];
		this.loopLength = track.loopLength ? track.loopLength : 6; // loop duration in seconds - actually the time between successive starts, signal plays for 1 1/2 times the loop length
		this.decayRate = track.decayRate;
		this.decayCutoff = track.decayCutoff;

		// Add the GUI element to the mixer
		let mixerGUI = document.getElementById('resonanceMixer');
		this.mixerTrack = document.createElement('div');
		this.mixerTrack.classList.add('mixerTrack');
		mixerGUI.appendChild(this.mixerTrack);

		// load the file and create Tone.js player
		let buffer = new Tone.Buffer(sampleFilePath + this.fileName, ()=>{this.length = buffer.duration;})
		let buffer2 = new Tone.Buffer(sampleFilePath + this.fileName, ()=>{})
		this.player = new Tone.Player(buffer);
		this.player.autostart = true;
		this.player.loop = true;
		this.player.fadeIn = this.loopLength / 2.;
		this.player.fadeOut = this.loopLength / 2.;
		// set up for looping
		this.player2 = new Tone.Player(buffer2); // used in loopPoint messages
		this.player2.autostart = false;
		this.player2.loop = false;
		this.player2.fadeIn = this.loopLength / 2.;
		this.player2.fadeOut = this.loopLength / 2.;
		this.looping = false;
		this.nextLoopPlayer = this.player;
		// for now just always 50% overlap, linear fade up and down, listen to it

		// create and connect audio nodes
		this.userGain = sound.context.createGain();
		this.dataGain = sound.context.createGain();
		this.decayGain = sound.context.createGain();
		this.player.connect(this.userGain);
		this.userGain.connect(this.dataGain);
		this.dataGain.connect(this.decayGain);
		this.decayGain.connect(sound.masterGain);

		// create & activate the mixer GUI elements
		this.userGainSlider = Track.createSlider(track.gain);
		this.userGain.gain.value = Math.pow(10, this.userGainSlider.value/20);
		this.userGainSlider.classList.add('userGainSlider');
		this.userGainSlider.addEventListener('input', ()=>{
			this.userGain.gain.setTargetAtTime(Math.pow(10, this.userGainSlider.value/20), sound.context.currentTime, 0.1);
		});

		this.dataGainSlider = Track.createSlider();
		this.dataGainSlider.classList.add('dataGainSlider');
		this.dataGainSlider.setAttribute('disabled', true);
		this.dataGain.gain.setTargetAtTime(0, sound.context.currentTime, 0.1);

		this.decayGainSlider = Track.createSlider();
		this.decayGainSlider.classList.add('decayGainSlider');
		this.decayGainSlider.setAttribute('disabled', true);

		// set up track inputs
		track.inputs.map(input => this.createInput(input));

		// display the GUI
		let infoGUI = document.createElement('div');
		infoGUI.innerText = this.fileName;
		infoGUI.setAttribute('class','mixerTrackInfo');
		this.mixerTrack.appendChild(infoGUI);

		let slidersGUI = document.createElement('div');
		slidersGUI.setAttribute('class','mixerTrackSliders');
		slidersGUI.appendChild(this.userGainSlider);
		slidersGUI.appendChild(this.dataGainSlider);
		slidersGUI.appendChild(this.decayGainSlider);
		this.mixerTrack.appendChild(slidersGUI);


		// display info about inputs
		this.inputsGUI = document.createElement('table');
		this.displayInputs();
		this.inputsGUI.setAttribute('class','mixerTrackInputs')
		this.mixerTrack.appendChild(this.inputsGUI);
	}

	static createSlider(gain) { // default gain value
		let slider = document.createElement('input');
		slider.setAttribute('class', 'h-slider');
		slider.setAttribute('type', 'range');
		slider.setAttribute('min', '-20');
		slider.setAttribute('max', '0');
		slider.setAttribute('step', '1');
		slider.setAttribute('value', gain ? gain : -10);
		slider.setAttribute('orient', 'horizonal');
		return slider;
	}

	static processMessage(message) {
		// searches the list of tracks and inputs for matching message channel
		sound.tracks.forEach((track)=>{
			track.update(message);
		})
	}

	displayInputs () {
		this.inputsGUI.innerHTML = '';
		this.inputs.forEach((input) => {

			let signal = sound.signals[Signal.getChannel(input.range)];
			let range = signal.ranges[input.range];
			let newInput = document.createElement('tr');
			newInput.innerHTML = `
				<td class='input-type'>${input.type}</td>
				<td class='input-data'>${input.value}</td>
				<td class='input-range'>${input.range}</td>
				<td class='input-minpeakmax'>${input.min}</td>
				<td class='input-minpeakmax'>${input.peak}</td>
				<td class='input-minpeakmax'>${input.max}</td><td>of</td>
				<td class='input-data'>${range.min}</td>
				<td class='input-data'>${range.max}</td>
				<td class='input-data'>${signal[input.value].toFixed(3)}</td>
				<td class='input-data'><b>${input.current.toFixed(3)}<b></td>
				<td class='input-data'>${input.decayValue.toFixed(3)}</td>`
			this.inputsGUI.appendChild(newInput);
		})

	}

	createInput(input) {
		this.inputs.push(new Input(input))
	}

	calculateValue(input, range, channel) {
		// got a message and matched it with an input to this track.
		let value = sound.signals[channel][input.value];
		let rangeSpread = range.max - range.min;

		// determine the range of the signal we are looking for
		let inputMin = (input.min * rangeSpread) + range.min ;
		let inputMax = (input.max * rangeSpread) + range.min ;
		let inputPeak = (input.peak * rangeSpread) + range.min;


		let newValue = 0;

		// if range min and max are the same, signal is always on
		if (inputMax == inputMin) {
			newValue = 1;
		}
		// case where the peak equals the max means it stays on above the max
		else if (inputMax == inputPeak) {
			newValue = (value - inputMin)/(inputMax-inputMin);
		}
		// case where the peak equals min, it stays on below min
		else if (inputMin == inputPeak) {
			newValue = 1 - ((value - inputMin)/(inputMax-inputMin));
		}
		// otherwise signal value depends on whether it is above or below peak
		else if (value > inputMin && value < inputPeak) {
			newValue = (value - inputMin)/(inputPeak-inputMin);
		}
		else if (value >= inputPeak && value < inputMax) {
			newValue = 1 - ((value - inputPeak)/(inputMax-inputPeak));
		}

		// clean up out-of-range values
		if (newValue < 0) {newValue = 0}
		if (newValue > 1) {newValue = 1}

		return newValue; // returns a number from 0 to 1 for this input
	}

	update (message) {
		let gainChanged = false; // allows for several volume inputs to same track, they are multiplied
		let changedGain = 0;
		let newGain;
		let ranges = sound.signals[message.address].ranges;



		this.inputs.forEach((input) => {
			for (const rangeName in ranges) {
				let range = ranges[rangeName];
				if (input.range == range.name){

					if (input.type === 'volume' ) { // calculates results of all volume inputs when it sees the first one

						newGain = this.calculateValue(input, range, message.address);
						input.updateDecay(newGain);
					}

					if (input.type == 'loopPoint') {
						// adjust looping behaviour
						// calculate at what point of the file to start
						let value  = this.calculateValue(input, range, message.address)

						input.updateDecay(value);

						let startPoint = value*(this.length-this.loopLength);

						// calculate "momentum" bsed on current signal vs average
						let momentum = (sound.signals[Signal.getChannel(input.range)].curr - sound.signals[Signal.getChannel(input.range)].avg3)*this.length*0.05; // not safe for all channels!
						//let momentum = 0.01*this.length;
						//let momentum = 0

						if (!this.looping) {
							this.player.stop(sound.context.currentTime + (this.loopLength / 2));
							this.player2.start(sound.context.currentTime, startPoint, sound.context.currentTime + 1.5*this.loopLength);
							this.looping = true;
						}
						clearTimeout(this.nextLoop);
						this.triggerNextGrain(startPoint, momentum);
					}

					if (input.type == 'playbackRate') {
						let value = this.calculateValue(input, range, message.address);
						input.updateDecay(value);

						let playbackMin = input.playbackMin;
						let playbackTimes = input.playbackSpeedup;


						let newRate = playbackMin + value*playbackTimes;
						newRate = Number(newRate.toFixed(4));

						this.player.playbackRate = newRate;
						this.player2.playbackRate = newRate;
					}
				}
			}
		})

		// calculate track decay

		let newDecayGain = this.inputs.reduce((sum, input) => {
			return sum + input.decayValue;
		}, 0)/this.inputs.length;


		this.decayGainSlider.value = (newDecayGain * 20) - 20;
		let targetGain = Math.pow(10, this.decayGainSlider.value/20);
		if (newDecayGain < this.decayCutoff) {targetGain = 0;}
		// ramps to new gain in 3 seconds
		this.decayGain.gain.setTargetAtTime(targetGain, sound.context.currentTime, 3);


		// calculate the track volume

		newGain = this.inputs.reduce((product, input) => {
			if (input.type === 'volume') {
				return product * input.current;
			}
			return product;
		}, 1);

		this.dataGainSlider.value = (newGain * 20) - 20;
		targetGain = Math.pow(10, this.dataGainSlider.value/20);
		if (newGain == 0) {targetGain = 0;}
		// ramps to new gain in 3 seconds
		this.dataGain.gain.setTargetAtTime(targetGain, sound.context.currentTime, 3);

		this.displayInputs();
	}

	triggerNextGrain(startPoint, momentum) {

		// catch the cases where momentum takes us outside of bounds
		if (startPoint > (this.length - 1.5*(this.loopLength) - momentum )) { startPoint = this.length - 1.5*(this.loopLength) - momentum - 1};
		if (startPoint < 0)  {startPoint = 0};

		this.nextLoopPlayer.start(sound.context.currentTime, startPoint, sound.context.currentTime + 1.5*this.loopLength);
		this.nextLoopPlayer == this.player ? this.nextLoopPlayer = this.player2 : this.nextLoopPlayer = this.player;

		if (sound.context.state == 'running') {
			this.nextLoop = setTimeout(()=>{this.triggerNextGrain(startPoint + momentum, momentum)}, this.loopLength*1000);
		}
		return true;
	}

	getJSON() {
		let preset = { 'fileName': this.fileName, 'gain' : this.userGainSlider.value, 'loopLength': this.loopLength, 'decayCutoff': this.decayCutoff }
		preset.inputs = this.inputs.map((input)=>{
			return {'range':input.range, 'type': input.type, 'value': input.value, 'min': input.min, 'peak': input.peak, 'max': input.max, 'decayRate': input.decayRate, 'decayRange': input.decayRange }
		})
		return preset;
	}
}


// A range is a selected range of the signal that tracks can control a track
class Range {
	constructor (range) {
		this.name = range.name;
		this.min = range.min ? range.min : null;
		this.max = range.max ? range.max : null;
		this.value = range.value ? range.value : 'curr';
		this.relative = range.relative ? range.relative : false;
	}

	update () {

		if (this.relative) {
			let channel = Signal.getChannel(this.name);
			let newValue = sound.signals[channel][this.value];
			if (this.max === null ) {
				this.max = Number(newValue.toFixed(2));
				this.min = Number(newValue.toFixed(2));
			}
			if (newValue > this.max) {
				this.max = Number(newValue.toFixed(2));
			}
			if (newValue < this.min) {
				this.min = Number(newValue.toFixed(2));
			}
		}
	}
}

// Interfaces between ranges and tracks. A track can have several inputs.
class Input {
	constructor (input) {
		this.range = input.range;
		this.type = input.type;
		this.value = input.value; // 'curr', 'avg3', 'avg5', 'avg10'
		this.min = input.min;
		this.peak = input.peak;
		this.max = input.max;
		this.current = 0;
		this.playbackMin = input.playbackMin ? input.playbackMin : 1;
		this.playbackSpeedup = input.playbackSpeedup ? input.playbackSpeedup : 1;
		this.decayRate = input.decayRate ? input.decayRate : 0.5;
		this.decayBoost = input.decayBoost ? input.decayBoost : 0.2;
		this.decayThreshold = input.decayThreshold ? input.decayThreshold : 0.7;
		this.decayRange = input.decayRange ? input.decayRange: 0.2;
		this.decayTarget = null;
		this.decayValue = 0;
	}

	updateDecay (value) {
		// if the decay Target is not yet defined, set it to the current value and return 1 or no decay.
		this.current = value;
		if (this.decayTarget === null) {
			this.decayTarget = value;
			//this.decayValue = this.decayThreshold;
			this.decayValue = this.decayBoost;
			return 1;
		}


		// if the value is within the range of the decay target, apply one step of decay and return the new decay value.
		if ( Math.abs(this.decayTarget - value) < this.decayRange ) {
			this.decayValue = this.decayValue * this.decayRate;
			return this.decayValue;
		}

		// if you get this far it means the value is outside of the the range
		this.decayValue = this.decayValue + this.decayBoost
		if (this.decayValue > this.decayThreshold) {
			this.decayTarget = value;
		}
		if (this.decayValue > 1) {this.decayValue = 1}
		return this.decayValue;
	}
}



/// HANDLING OSC RECORDINGS/PLAYBACK

class OSCPlayer {
	constructor() {
		this._playing = false;
		this._currentEvent = 0;
		this._nextEvent = null;
		this.timeout = null;
		this.events = [];

		this.loadOSCEvents = () => {
			let fileName = document.getElementById('OSCEventFile').value.split('\\');
			fileName = fileName[fileName.length - 1];

			if (fileName !== '') {
				fetch(eventsFilePath + fileName)
					.then(response => response.text())
					.then(events => {
						this.events = JSON.parse(events);
						document.getElementById('toggleOSC').removeAttribute('disabled');
						document.getElementById('resetOSC').removeAttribute('disabled');
					})
			}
		}

		this.toggleOSC = () => {
			let button = document.getElementById('toggleOSC');
			if (this._playing) {
				this.cancelNextEvent();
				button.innerText = 'Play OSC';
			} else {
				this.playOSC();
				button.innerText = 'Pause OSC';
			}
		}

		this.playOSC = () => {
			console.log('playing OSC');
			this._playing = true;
			this.playEvent(this._currentEvent);
		}

		this.playEvent = (i) => {
			if (i < this.events.length) {
				this._currentEvent = i;
				// message processing goes here!
				console.log(this.events[i].message);
				Signal.processMessage(this.events[i].message);
				this.sequenceNextEvent(i);
			}
		}

		this.sequenceNextEvent = (i) => {
			if (i + 1 < this.events.length) {
				let delay = this.events[i+1].time - this.events[i].time;
				// SAMPLE RATE PATCH - for WSAS07 uncomment this
				//delay = delay/4;
				this.timeout = setTimeout(this.playEvent, delay, i+1);
			} else { console.log('reached end of OSC')};
		}

		this.cancelNextEvent = () => {
			clearTimeout(this.timeout);
			this._playing = false;
		}

		this.setOSCStep = (step) => {
			this._currentEvent = step;
		}

		this.resetOSC = () => {
			if (this.playing) {
				this.toggleOSC();
			}
			oscPlayer.setOSCStep(0);
		}
	}

	get playing() {
		return this._playing;
	}
}

class OSCRecorder {
	constructor() {
		this._recording = false;
		this.timeStarted = null;
		let events = [];
		console.log('created OSC recorder');

		this.startRecording = () => {
			this._recording = true;
			this.timeStarted = Date.now();
			console.log('OSC started recording at ' + this.timeStarted);
		}

		this.stopRecording = () => {
			this._recording = false;
			console.log('OSC stopped recording');
			console.log(events);
			this.saveEvents();
			this.timeStarted = null;
			events = [];
		}

		this.toggleRecording = () => {
			if (this._recording) {
				this.stopRecording();
			} else this.startRecording();
		}

		this.receiveMessage = (message) => {
			if (this._recording) {
				events.push({'time': Date.now() - this.timeStarted, 'message': message});
			}
		}

		this.saveEvents = () => {
			console.log('saving events to file');
			// this is a hacky way of saving a text file
		    var a = document.createElement("a");
		    var file = new Blob([JSON.stringify(events)], {type: 'text/plain'});
		    a.href = URL.createObjectURL(file);
		    a.download = 'oscEvents.txt';
		    a.innerHTML = a.download;
		    let dummy = document.getElementById('resonancePlayer');
		    dummy.appendChild(a);
		    a.click();
		    dummy.removeChild(a);
		    URL.revokeObjectURL(a.href);
		}

		this.play = () => {
			playOSCEvents(events);
		}
	}

	set recording (value) {
		console.log('recording: ' + value);
		this._recording = value;
	}

	get recording () {
		return this._recording;
	}
}

// INITIALIZE ENVIRONEMENT BEFORE LOADING AUDIO

// assign proper functions to GUI buttons
window.onload = function () {
	document.getElementById('startContextButton').addEventListener("click", () => { startAudio(defaultPreset) });
	document.getElementById('loadPresetButton').addEventListener('click', () => { loadPreset() });
	document.getElementById('savePresetButton').addEventListener('click', () => { savePreset() });
	document.getElementById('loadOSC').addEventListener('click', () => { oscPlayer.loadOSCEvents() });
	document.getElementById('toggleOSC').addEventListener("click", () => { oscPlayer.toggleOSC() });
	document.getElementById('resetOSC').addEventListener("click", () => { oscPlayer.resetOSC() });
	document.getElementById('recordOSC').addEventListener("click", () => { oscRecorder.toggleRecording() });
}

// websocket for receiving messages
const socket = io('http://127.0.0.1:5000');

socket.on('connect', function() {
	socket.emit('my event', {data: "New connection!"})
})

socket.on('event', function(message){
	oscRecorder.receiveMessage(message);
	Signal.processMessage(message);
});

// instantiate objects

const oscPlayer = new OSCPlayer();
const oscRecorder = new OSCRecorder();

// handling presets
function loadPreset() {
	let fileName = document.getElementById('presetFileInput').value.split('\\');
	fileName = fileName[fileName.length - 1];

	if (fileName !== '') { // check if input field is blank
		fetch('static/playerPresets/' + fileName)
			.then(response => response.text())
			.then(preset => {
				startAudio(JSON.parse(preset));
			})
	} else {
		console.log('please select a preset file from the playerPresets folder');
	}
}

function savePreset() {
	console.log('saving app state as preset');
	// this is a hack for saving a file from the front-end
    var a = document.createElement("a");
    let tracksJSON = sound.tracks.map(track => track.getJSON());
    var file = new Blob([JSON.stringify(tracksJSON)], {type: 'text/plain'});
    a.href = URL.createObjectURL(file);
    a.download = 'preset.txt';
    a.innerHTML = a.download;
    document.getElementById('resonancePlayer').appendChild(a);
    a.click();
    document.getElementById('resonancePlayer').removeChild(a);
    URL.revokeObjectURL(a.href);
}


// initializing page
function startAudio(preset) {
	console.log('audio started!');

	// remove the start context button
	const button = document.getElementById('startContextButton')
	if (button) {button.parentNode.removeChild(button);}

	document.getElementById('mainControls').removeAttribute('style');

	sound.context = new AudioContext();
	sound.context.suspend();
	Tone.context = sound.context;

	sound.masterGain = sound.context.createGain();
	sound.filter = new Tone.Filter(8000, 'lowpass');

	Tone.connect(sound.masterGain, sound.filter);
	sound.filter.connect(sound.context.destination);

	// activate main GUI buttons
	const playButton = document.getElementById('startAudio');
	playButton.addEventListener('click', ()=>{
		sound.context.resume();
	})

	const stopButton = document.getElementById('stopAudio');
	stopButton.addEventListener('click', ()=>{sound.context.suspend()})

	const masterGainSlider = document.getElementById('masterGain');
	sound.masterGain.gain.value = Math.pow(10, masterGainSlider.value/20);
	masterGainSlider.addEventListener('input', ()=> {
		sound.masterGain.gain.setTargetAtTime(Math.pow(10, masterGainSlider.value/20),sound.context.currentTime, 0.1);
	}, false);



	// initalize list of channels
	preset.signals.map(signal => loadSignal(signal));

	//load the selected preset
	preset.tracks.map(track => loadTrack(track));

	console.log(sound);

	sound.context.resume();
}

function loadTrack(track) {
	sound.tracks.push(new Track(track));
}

function loadSignal(signal) {
	sound.signals[signal.channel] = new Signal(signal);
}
