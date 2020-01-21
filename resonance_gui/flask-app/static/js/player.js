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
					min: 0.53,
					max: 0.67
				},
				{
					name: 'fp_dpli_left_midline_mid',
					min: 0.47,
					max: 0.53
				},
				{
					name: 'fp_dpli_left_midline_lag',
					min: 0.33,
					max: 0.47
				}
			]
		},
		{ 	channel: '/fp_dpli_left_lateral',
			ranges: [
				{
					name: 'fp_dpli_left_lateral_lead',
					min: 0.53,
					max: 0.67
				},
				{
					name: 'fp_dpli_left_lateral_mid',
					min: 0.47,
					max: 0.53
				},
				{
					name: 'fp_dpli_left_lateral_lag',
					min: 0.33,
					max: 0.47
				}
			]
		},
		{ 	channel: '/fp_dpli_right_midline', 
			ranges: [
				{
					name: 'fp_dpli_right_midline_lead',
					min: 0.53,
					max: 0.67
				},
				{
					name: 'fp_dpli_right_midline_mid',
					min: 0.47,
					max: 0.53
				},
				{
					name: 'fp_dpli_right_midline_lag',
					min: 0.33,
					max: 0.47
				}
			]
		},
		{ 	channel: '/fp_dpli_right_lateral',
			ranges: [
				{
					name: 'fp_dpli_right_lateral_lead',
					min: 0.53,
					max: 0.67
				},
				{
					name: 'fp_dpli_right_lateral_mid',
					min: 0.47,
					max: 0.53
				},
				{
					name: 'fp_dpli_right_lateral_lag',
					min: 0.33,
					max: 0.47
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
			ranges: []
		},
		{ 	channel: '/pe_frontal', 
			ranges: [
				{
					name: 'pe_frontal',
					min: 0.6,
					max: 0.7
				},
				{	name: 'pe_frontal_high',
					min: 0.84,
					max: 1
				}
			]
		},
		{ 	channel: '/pe_parietal', 
			ranges: [
				{
					name: 'pe_parietal',
					min: 0.6,
					max: 0.7
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
					min: 0.2,
					max: 0.22,
				},
				{
					name: 'spr_beta_alpha_low',
					min: 0.26,
					max: 0.32,
				},
				{
					name: 'spr_beta_alpha_high',
					min: 0.28,
					max: 0.4
				}
			]
		},
		{ 	channel: '/spr_alpha_theta', 
			ranges: [
				{
					name: 'spr_alpha_theta_fullrange',
					min: 0,
					max: 1.3
				},
				{
					name: 'spr_alpha_theta_high',
					min: 0.3,
					max: 0.35
				}
			]
		},
		{ 	channel: '/td_front_back',
			ranges: []
		}
	],
	tracks: [
	{	fileName: 'harpascending.ogg', 
		gain: -10,
		loopLength: 5,
		decayCutoff: 0.1,
		inputs: [{ 	range:'spr_beta_alpha_high',
					type:'loopPoint',
					value:'curr',
					min: 0, 
					peak: 1, 
					max: 1,
					decayBoost: 0.4,
					decayRate: 0.8,
					decayRange: 0.1
				},
				{ 	range:'spr_beta_alpha_high', 
					type:'volume',
					value:'curr',
					min: 0, 
					peak: 0.8, 
					max: 1,
					decayRate: 0.8,
					decayRange: 0.1
				}
				]
	},
	{ 	fileName: 'softersynth.ogg',
		gain: -10,
		loopLength: 6,
		decayCutoff: 0.1,
		inputs: [{	range:'spr_beta_alpha_low',
					type:'loopPoint',
					value: 'avg3',
					min: 0,
					peak: 1,
					max: 1,
					decayRate: 0.5,
					decayRange: 0.25 },
				{	range:'spr_beta_alpha_low',
					type:'volume',
					value: 'avg3',
					min: 0,
					peak: 0.8,
					max: 1,
					decayRate: 0.5,
					decayRange: 0.25 }
				]
	},
	{	fileName: 'pianoascending.ogg', 
		gain: -10,
		loopLength: 5,
		decayCutoff: 0.1,
		inputs: [{ 	range:'spr_alpha_theta_high',
					type:'loopPoint',
					value:'curr',
					min: 0, 
					peak: 1, 
					max: 1,
					decayRate: 0.6,
					decayRange: 0.2 },
				{ 	range:'spr_alpha_theta_high', 
					type:'volume',
					value:'curr',
					min: 0, 
					peak: 0.8, 
					max: 1,
					decayRate: 0.6,
					decayRange: 0.2 }
				]
	},
	// {	fileName: 'fractalmusic.ogg',
	// 	gain: -10,
	// 	loopLength: 6,
	// 	decayCutoff: 0.1,
	// 	inputs: [{	range: 'spr_alpha_theta_fullrange',
	// 				type: 'volume',
	// 				value: 'avg3',
	// 				min: 0,
	// 				peak: 0.5,
	// 				max: 1,
	// 				decayRate: 0.7,
	// 				decayRange: 0.2 
	// 			},{	
	// 				range: 'spr_alpha_theta_fullrange',
	// 				type: 'loopPoint',
	// 				value: 'curr',
	// 				min: 0,
	// 				peak: 1,
	// 				max: 1,
	// 				decayRate: 0.7,
	// 				decayRange: 0.2 

	// 	}]

	// },
	{	fileName: 'slow_gloc_melody.ogg',
		gain: -10,
		inputs: [{	range: 'spr_beta_alpha_gloc',
					type: 'volume',
					value: 'curr',
					min: 0,
					peak: 0,
					max: 1,
					decayRate: 0.7,
					decayRange: 0.2 
		}]
	},
	{	fileName: 'dPLI-LL-celesta.ogg', 
		gain: -10,
		loopLength: 1.5,
		decayCutoff: 0.1,
		inputs: [{ 	range:'fp_dpli_left_lateral_lag', 
					type:'loopPoint',
					value: 'curr',
					min: 0, 
					peak: 0, 
					max: 1,
					decayRate: 0.6,
					decayRange: 0.1 },
				{ 	range:'fp_dpli_left_lateral_lag', 
					type:'volume', 
					value: 'curr',
					min: 0.7, 
					peak: 0.7, 
					max: 0.95,
					decayBoost: 0.5,
					decayRate: 0.6,
					decayRange: 0.1 },
				{ 	range:'fp_wpli_left_lateral_lag', 
					type:'volume',
					value: 'curr',
					min: 0, 
					peak: 1, 
					max: 1,
					decayRate: 0.6,
					decayRange: 0.1 }
				]
	},
	{	fileName: 'dPLI-LM-marimba.ogg', 
		gain: -10,
		loopLength: 1.5,
		decayCutoff: 0.1,
		inputs: [{ 	range:'fp_dpli_left_midline_lag', 
					type:'loopPoint',
					value: 'curr',
					min: 0, 
					peak: 0, 
					max: 1,
					decayRate: 0.6,
					decayRange: 0.1 },
				{ 	range:'fp_dpli_left_midline_lag', 
					type:'volume', 
					value: 'curr',
					min: 0.7, 
					peak: 0.7, 
					max: 0.95,
					decayBoost: 0.5,
					decayRate: 0.6,
					decayRange: 0.1 },
				{ 	range:'fp_wpli_left_midline_lag', 
					type:'volume',
					value: 'curr',
					min: 0, 
					peak: 1, 
					max: 1,
					decayRate: 0.6,
					decayRange: 0.1 }
				]
	},
	{	fileName: 'dPLI-RM-xylophone.ogg', 
		gain: -10,
		loopLength: 1.5,
		decayCutoff: 0.1,
		inputs: [{ 	range:'fp_dpli_right_midline_lag', 
					type:'loopPoint',
					value: 'curr',
					min: 0, 
					peak: 0, 
					max: 1,
					decayBoost: 0.5,
					decayRate: 0.6,
					decayRange: 0.1 },
				{ 	range:'fp_dpli_right_midline_lag', 
					type:'volume', 
					value: 'curr',
					min: 0.7, 
					peak: 0.7, 
					max: 0.95,
					decayRate: 0.6,
					decayRange: 0.1 },
				{ 	range:'fp_wpli_right_midline_lag', 
					type:'volume',
					value: 'curr',
					min: 0, 
					peak: 1, 
					max: 1,
					decayRate: 0.6,
					decayRange: 0.1 }
				]
	},
	{	fileName: 'dPLI-RL-vibraphone.ogg', 
		gain: -10,
		loopLength: 1.5,
		decayCutoff: 0.1,
		inputs: [{ 	range:'fp_dpli_right_lateral_lag', 
					type:'loopPoint',
					value: 'curr',
					min: 0, 
					peak: 0, 
					max: 1,
					decayRate: 0.6,
					decayRange: 0.1 },
				{ 	range:'fp_dpli_right_lateral_lag', 
					type:'volume', 
					value: 'curr',
					min: 0.7, 
					peak: 0.7, 
					max: 0.95,
					decayBoost: 0.5,
					decayRate: 0.6,
					decayRange: 0.1 },
				{ 	range:'fp_wpli_right_lateral_lag', 
					type:'volume',
					value: 'curr',
					min: 0, 
					peak: 1, 
					max: 1,
					decayRate: 0.6,
					decayRange: 0.1 }
				]
	},

	// positive values of dPLI
	{	fileName: 'dPLI-LL-celesta.ogg', 
		gain: -10,
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
					min: 0.05, 
					peak: 0.3, 
					max: 0.3,
					decayBoost: 0.5,
					decayRate: 0.6,
					decayRange: 0.1 },
				{ 	range:'fp_wpli_left_lateral_lead', 
					type:'volume',
					value: 'curr',
					min: 0, 
					peak: 1, 
					max: 1,
					decayRate: 0.6,
					decayRange: 0.1 }
				]
	},
	{	fileName: 'dPLI-LM-marimba.ogg', 
		gain: -10,
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
					min: 0.05, 
					peak: 0.3, 
					max: 0.3,
					decayBoost: 0.5,
					decayRate: 0.6,
					decayRange: 0.1 },
				{ 	range:'fp_wpli_left_midline_lead', 
					type:'volume',
					value: 'curr',
					min: 0, 
					peak: 1, 
					max: 1,
					decayRate: 0.6,
					decayRange: 0.1 }
				]
	},
	{	fileName: 'dPLI-RM-xylophone.ogg', 
		gain: -10,
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
					min: 0.05, 
					peak: 0.3, 
					max: 0.3,
					decayBoost: 0.5,
					decayRate: 0.6,
					decayRange: 0.1 },
				{ 	range:'fp_wpli_right_midline_lead', 
					type:'volume',
					value: 'curr',
					min: 0, 
					peak: 1, 
					max: 1,
					decayRate: 0.6,
					decayRange: 0.1 }
				]
	},
	{	fileName: 'dPLI-RL-vibraphone.ogg', 
		gain: -10,
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
					min: 0.05, 
					peak: 0.3, 
					max: 0.3,
					decayBoost: 0.5,
					decayRate: 0.6,
					decayRange: 0.1 },
				{ 	range:'fp_wpli_right_lateral_lead', 
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
		fileName: 'wPLI-LL-flute-low.ogg',
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
					decayRange: 0.35
				},
				{	range: 'fp_dpli_left_lateral_lag',
					type: 'volume',
					value: 'avg3',
					min: 0,
					peak: 0,
					max: 1,
					decayThreshold: 0.4,
					decayBoost: 0.1,
					decayRate: 0.4,
					decayRange: 0.35
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
					decayRange: 0.35
				},
				{	range: 'fp_dpli_left_lateral_mid',
					type: 'volume',
					value: 'avg3',
					min: 0,
					peak: 0.5,
					max: 1,
					decayThreshold: 0.4,
					decayBoost: 0.1,
					decayRate: 0.4,
					decayRange: 0.35
				}
			]
	},
	{
		fileName: 'wPLI-LL-flute-high.ogg',
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
					decayRange: 0.35
				},
				{	range: 'fp_dpli_left_lateral_lead',
					type: 'volume',
					value: 'avg3',
					min: 0,
					peak: 1,
					max: 1,
					decayThreshold: 0.4,
					decayBoost: 0.1,
					decayRate: 0.4,
					decayRange: 0.35
				}
			]
	},
	{
		fileName: 'wPLI-LM-bassoon-low.ogg',
		gain: -10,
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
					decayRange: 0.35
				},
				{	range: 'fp_dpli_left_midline_lag',
					type: 'volume',
					value: 'avg3',
					min: 0,
					peak: 0,
					max: 1,
					decayThreshold: 0.4,
					decayBoost: 0.1,
					decayRate: 0.4,
					decayRange: 0.35
				}
			]
	},
	{
		fileName: 'wPLI-LM-bassoon-mid.ogg',
		gain: -10,
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
					decayRange: 0.35
				},
				{	range: 'fp_dpli_left_midline_mid',
					type: 'volume',
					value: 'avg3',
					min: 0,
					peak: 0.5,
					max: 1,
					decayThreshold: 0.4,
					decayBoost: 0.1,
					decayRate: 0.4,
					decayRange: 0.35
				}
			]
	},
	{
		fileName: 'wPLI-LM-bassoon-high.ogg',
		gain: -10,
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
					decayRange: 0.35
				},
				{	range: 'fp_dpli_left_midline_lead',
					type: 'volume',
					value: 'avg3',
					min: 0,
					peak: 1,
					max: 1,
					decayThreshold: 0.4,
					decayBoost: 0.1,
					decayRate: 0.4,
					decayRange: 0.35
				}
			]
	},
	{
		fileName: 'wPLI-RM-horn-low.ogg',
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
					decayRange: 0.35
				},
				{	range: 'fp_dpli_right_midline_lag',
					type: 'volume',
					value: 'avg3',
					min: 0,
					peak: 0,
					max: 1,
					decayThreshold: 0.4,
					decayBoost: 0.1,
					decayRate: 0.4,
					decayRange: 0.35
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
					decayRange: 0.35
				},
				{	range: 'fp_dpli_right_midline_mid',
					type: 'volume',
					value: 'avg3',
					min: 0,
					peak: 0.5,
					max: 1,
					decayThreshold: 0.4,
					decayBoost: 0.1,
					decayRate: 0.4,
					decayRange: 0.35
				}
			]
	},
	{
		fileName: 'wPLI-RM-horn-high.ogg',
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
					decayRange: 0.35
				},
				{	range: 'fp_dpli_right_midline_lead',
					type: 'volume',
					value: 'avg3',
					min: 0,
					peak: 1,
					max: 1,
					decayThreshold: 0.4,
					decayBoost: 0.1,
					decayRate: 0.4,
					decayRange: 0.35
				}
			]
	},
	{
		fileName: 'wPLI-RL-clarinet-low.ogg',
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
					decayRange: 0.35
				},
				{	range: 'fp_dpli_right_lateral_lag',
					type: 'volume',
					value: 'avg3',
					min: 0,
					peak: 0,
					max: 1,
					decayThreshold: 0.4,
					decayBoost: 0.1,
					decayRate: 0.4,
					decayRange: 0.35
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
					decayRange: 0.35
				},
				{	range: 'fp_dpli_right_lateral_mid',
					type: 'volume',
					value: 'avg3',
					min: 0,
					peak: 0.5,
					max: 1,
					decayThreshold: 0.4,
					decayBoost: 0.1,
					decayRate: 0.4,
					decayRange: 0.35
				}
			]
	},
	{
		fileName: 'wPLI-RL-clarinet-high.ogg',
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
					decayRange: 0.35
				},
				{	range: 'fp_dpli_right_midline_lead',
					type: 'volume',
					value: 'avg3',
					min: 0,
					peak: 1,
					max: 1,
					decayThreshold: 0.4,
					decayBoost: 0.1,
					decayRate: 0.4,
					decayRange: 0.35
				}
			]
	},
	{
		fileName: 'PE-noise.ogg',
		gain: -10,
		decayCutoff: 0.1,
		inputs: [{	range: 'pe_frontal',
					type: 'volume',
					value: 'avg3',
					min: 0.0,
					peak: 0.5,
					max: 1,
					decayRate: 0.5,
					decayRange: 0.3,
					decayBoost: 0.1
		}]
	},
		{
		fileName: 'PE-noise2.ogg',
		gain: -10,
		decayCutoff: 0.1,
		inputs: [{	range: 'pe_parietal',
					type: 'volume',
					value: 'avg3',
					min: 0.0,
					peak: 0.5,
					max: 1,
					decayRate: 0.5,
					decayRange: 0.3,
					decayBoost: 0.1
		}]
	},
	{	fileName: 'microtwinkle.ogg',
		gain: -10,
		loopLength: 4,
		decayCutoff: 0.,
		inputs: [{	range:'pe_frontal_high',
					type: 'volume',
					value: 'curr',
					min: 0.0,
					peak: 0.4,
					max: 0.7,
					decayRate: 0.9,
					decayRange: 0.2 
				},
				{	range:'pe_frontal_high',
					type: 'loopPoint',
					value: 'avg3',
					min: 0,
					peak: 0.75,
					max: 1,
					decayBoost: 0.5,
					decayRate: 0.9,
					decayRange: 0.2

				}
			]

	}
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
		this.curr = null;
		this.prev = null;
		this.mute = false;
		this.last10 = [];
		this.ranges = signal.ranges;

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
		//console.log(message);
		sound.signals[message.address].update(message);
		Track.processMessage(message);
	}

	update (message) {
		// update last 10 messages
		if (this.last10.length == 10) { this.last10.shift(); }
		this.last10.push(message.args[0]);

		if (this.max === null || message.args[0] > this.max) {this.max = message.args[0]}
		if (this.min === null || message.args[0] < this.min) {this.min = message.args[0]}

		this.prev = this.curr;
		this.curr = message.args[0];

		this.avg3 = this.last10.slice(-3).reduce((a,c)=>{return a+c})/this.last10.slice(-3).length;
		this.avg5 = this.last10.slice(-5).reduce((a,c)=>{return a+c})/this.last10.slice(-5).length;
		this.avg10 = this.last10.slice(-10).reduce((a,c)=>{return a+c})/this.last10.slice(-10).length;

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
		this.loopLength = track.loopLength; // loop duration in seconds - actually the time between successive starts, signal plays for 1 1/2 times the loop length
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
		let inputsGUI = document.createElement('table');
		this.inputs.forEach((input) => {
			let newInput = document.createElement('tr');
			newInput.innerHTML = `<td>${input.range}</td><td>${input.type}</td>`
			inputsGUI.appendChild(newInput);
		})
		inputsGUI.setAttribute('class','mixerTrackInputs')
		this.mixerTrack.appendChild(inputsGUI);
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

		if (this.fileName === 'wPLI-RL-clar-mid.ogg') {
			if (message.address === '/fp_wpli_right_lateral' || message.address === '/fp_dpli_right_lateral'){
				console.log('RANGES');
				console.log(ranges);
			}
		}


		this.inputs.forEach((input) => {
			ranges.forEach((range) => {
				// console.log(input, range);
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
						//let momentum = (sound.signals[input.channel].curr - sound.signals[input.channel].avg3)*this.length*0.15; // not safe for all channels!
						//let momentum = 0.01*this.length;
						let momentum = 0;

						if (!this.looping) {
							this.player.stop(sound.context.currentTime + (this.loopLength / 2));
							this.player2.start(sound.context.currentTime, startPoint, sound.context.currentTime + 1.5*this.loopLength);
							this.looping = true;
						}
						clearTimeout(this.nextLoop);
						this.triggerNextGrain(startPoint, momentum);
					}
				}
			})
		})

		// calculate track decay

		let newDecayGain = this.inputs.reduce((sum, input) => { 
			//console.log(input.range, input.decayValue);
			if (this.fileName === 'wPLI-RL-clar-mid.ogg') {
				if (message.address === '/fp_wpli_right_lateral' || message.address === '/fp_dpli_right_lateral'){
					console.log('input = ' + input.range);
					console.log("decayValue = " + input.decayValue);
				}
			}
			return sum + input.decayValue;
		}, 0)/this.inputs.length;

		if (this.fileName === 'wPLI-RL-clar-mid.ogg') {
			if (message.address === '/fp_wpli_right_lateral' || message.address === '/fp_dpli_right_lateral'){
				console.log(message.address);
				console.log("newDecayGain = " + newDecayGain);
			}
		}

		this.decayGainSlider.value = (newDecayGain * 20) - 20;
		let targetGain = Math.pow(10, this.decayGainSlider.value/20);
		if (newDecayGain < this.decayCutoff) {targetGain = 0;}
		// ramps to new gain in 3 seconds
		this.decayGain.gain.setTargetAtTime(targetGain, sound.context.currentTime, 3);


		// calculate the track volume

		newGain = this.inputs.reduce((product, input) => {
			if (input.type === 'volume') {
				if (this.fileName === 'wPLI-RL-clar-mid.ogg') {
					if (message.address === '/fp_wpli_right_lateral' || message.address === '/fp_dpli_right_lateral'){
						console.log("input.range: " + input.range);
						console.log("input.current: " + input.current);
					}
				}
				return product * input.current;
			}
			return product;
		}, 1);

		if (this.fileName === 'wPLI-RL-clar-mid.ogg') {
			if (message.address === '/fp_wpli_right_lateral' || message.address === '/fp_dpli_right_lateral'){
				console.log(message.address);
				console.log("newGain = " + newGain);
			}
		}

		this.dataGainSlider.value = (newGain * 20) - 20;
		targetGain = Math.pow(10, this.dataGainSlider.value/20);
		if (newGain == 0) {targetGain = 0;}
		// ramps to new gain in 3 seconds
		this.dataGain.gain.setTargetAtTime(targetGain, sound.context.currentTime, 3);
	}

	triggerNextGrain(startPoint, momentum) {
		// catch the cases where momentum takes us outside of bounds
		if (startPoint > (this.length - 1.5*(this.loopLength) )) { startPoint = this.length - 1.5*(this.loopLength) };
		if (startPoint < 0)  {startPoint = 0};

		this.nextLoopPlayer.start(sound.context.currentTime, startPoint, sound.context.currentTime + 1.5*this.loopLength);
		this.nextLoopPlayer == this.player ? this.nextLoopPlayer = this.player2 : this.nextLoopPlayer = this.player;

		if (sound.context.state == 'running') {
			this.nextLoop = setTimeout(()=>{this.triggerNextGrain(startPoint + momentum, momentum)}, this.loopLength*1000);
		}
		return true;
	}

	display () {


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
		this.min = range.min;
		this.max = range.max;
	}

	update () {

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
		this.decayRate = input.decayRate;
		this.decayBoost = input.decayBoost ? input.decayBoost : 0.2;
		this.decayThreshold = input.decayThreshold ? input.decayThreshold : 0.7;
		this.decayRange = input.decayRange;
		this.decayTarget = null;
		this.decayValue = 0;
	}

	updateDecay (value) {
		// if the decay Target is not yet defined, set it to the current value and return 1 or no decay.
		this.current = value;
		if (this.decayTarget === null) {
			this.decayTarget = value;
			return 1;
		}

		// if the value is within the range of the decay target, apply one step of decay and return the new decay value.
		if ( Math.abs(this.decayTarget - value) < this.decayRange ) {
			this.decayValue = this.decayValue * this.decayRate;
			return this.decayValue;
		}

		// if you get this far it means the value is outside of the the range
		this.decayValue = this.decayValue + this.decayBoost
		if (this.decayValue > this.decayThresold) {
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
						console.log(this.events.length + ' events loaded');
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
		    let dummy = document.getElementById('messageArea');
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
	
	
}

// websocket for receiving messages
const socket = io('http://127.0.0.1:5000');

socket.on('connect', function() {
	socket.emit('my event', {data: "New connection!"})
})

socket.on('event', function(message){
	// oscRecorder.receiveMessage(data);
	//sound.signals[message.address].update(message);
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
	sound.masterGain.connect(sound.context.destination);

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
}

function loadTrack(track) {
	sound.tracks.push(new Track(track));
}

function loadSignal(signal) {
	sound.signals[signal.channel] = new Signal(signal);
}





