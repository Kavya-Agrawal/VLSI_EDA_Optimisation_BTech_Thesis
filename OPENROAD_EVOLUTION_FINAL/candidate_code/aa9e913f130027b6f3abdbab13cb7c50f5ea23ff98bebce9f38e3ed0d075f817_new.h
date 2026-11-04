// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.88808785;
  double density_weight = 0.32867040;
  double prefix_weight = 0.11697307;
  double neighborhood_weight = 0.36772521;
  double late_weight = 0.09208751;
  double critical_weight = 0.05224224;
  unsigned budget = 14;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
