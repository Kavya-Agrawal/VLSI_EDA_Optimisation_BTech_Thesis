// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.84530441;
  double density_weight = 0.59765045;
  double prefix_weight = 0.43450513;
  double neighborhood_weight = 0.16461693;
  double late_weight = 0.24651767;
  double critical_weight = 0.19145961;
  unsigned budget = 34;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
